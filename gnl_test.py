import sys
import os

# Add LLDB to Python path - trying both possible locations
lldb_paths = [
    '/usr/lib/llvm-15/lib/python3.10/dist-packages',
    '/usr/lib/llvm-15/lib/python3/dist-packages'
]

for path in lldb_paths:
    if os.path.exists(path) and path not in sys.path:
        sys.path.append(path)
        break

import lldb

class GNLTester:
    def __init__(self, program_path):
        # Initialize debugger
        self.debugger = lldb.SBDebugger.Create()
        self.debugger.SetAsync(False)
        
        # Create target
        self.target = self.debugger.CreateTarget(program_path)
        if not self.target:
            raise Exception("Couldn't create target")
        
        # Test tracking
        self.current_test_data = []
        self.actual_results = []
        self.memory_allocations = []
        self.buffer_states = []
        self.errors_found = []
        
        # Set up breakpoints
        self.setup_breakpoints()
        
    def setup_breakpoints(self):
        # Core function breakpoints
        self.main_bp = self.target.BreakpointCreateByName("get_next_line")
        self.read_bp = self.target.BreakpointCreateByName("read_into_buffer")
        self.fill_bp = self.target.BreakpointCreateByName("fill_str")
        self.flush_bp = self.target.BreakpointCreateByName("buffer_flushing")
        
        # Memory operation breakpoints
        self.malloc_bp = self.target.BreakpointCreateBySymbol("malloc")
        self.free_bp = self.target.BreakpointCreateBySymbol("free")

    def check_buffer_state(self, frame):
        buffer_val = frame.FindVariable("buf")
        if buffer_val.IsValid():
            # Get raw buffer data
            size = buffer_val.GetByteSize()
            data = [buffer_val.GetUnsignedInt8(i) for i in range(size)]
            self.buffer_states.append(data)
            return data
        return None

    def track_memory_operation(self, frame, is_malloc=True):
        if is_malloc:
            size = frame.GetValueForVariablePath("$arg1").GetValueAsUnsigned()
            addr = frame.GetThread().GetStopReturnAddress().GetLoadAddress(self.target)
            self.memory_allocations.append((addr, size))
        else:
            addr = frame.GetValueForVariablePath("$arg1").GetValueAsUnsigned()
            self.memory_allocations = [(a, s) for a, s in self.memory_allocations if a != addr]

    def create_test_file(self, content):
        fd, path = tempfile.mkstemp(text=True)
        os.write(fd, content.encode())
        os.close(fd)
        return path

    def run_single_test(self, test_content, test_name=""):
        test_file = self.create_test_file(test_content)
        try:
            self.current_test_data = test_content.splitlines(True)
            self.actual_results = []
            self.buffer_states = []
            self.memory_allocations = []
            self.errors_found = []

            # Launch process
            error = lldb.SBError()
            process = self.target.LaunchSimple([test_file], None, os.getcwd())
            
            if not process:
                raise Exception("Process launch failed")

            # Process until completion
            while process.GetState() == lldb.eStateStopped:
                thread = process.GetSelectedThread()
                frame = thread.GetSelectedFrame()
                
                self.check_current_state(frame)
                process.Continue()

            # Verify results
            result = self.verify_test_results()
            self.print_test_results(test_name)
            return result

        finally:
            os.unlink(test_file)

    def check_current_state(self, frame):
        func_name = frame.GetFunctionName()
        
        if func_name == "get_next_line":
            self.check_buffer_state(frame)
            ret_val = frame.GetReturnValue()
            if ret_val.IsValid():
                self.actual_results.append(ret_val.GetSummary())
        
        elif func_name == "malloc":
            self.track_memory_operation(frame, True)
        
        elif func_name == "free":
            self.track_memory_operation(frame, False)

    def verify_test_results(self):
        success = True
        
        # Check line count
        if len(self.actual_results) != len(self.current_test_data):
            self.errors_found.append(
                f"Line count mismatch: expected {len(self.current_test_data)}, got {len(self.actual_results)}"
            )
            success = False

        # Check line content
        for i, (actual, expected) in enumerate(zip(self.actual_results, self.current_test_data)):
            if not self.verify_line(actual, expected):
                self.errors_found.append(f"Line {i+1} mismatch: expected {expected!r}, got {actual!r}")
                success = False

        # Check memory leaks
        if self.memory_allocations:
            self.errors_found.append(f"Memory leak detected: {len(self.memory_allocations)} allocations not freed")
            success = False

        return success

    def verify_line(self, returned_line, expected_line):
        if returned_line is None and expected_line is None:
            return True
            
        if returned_line is None:
            return False
            
        # Clean up the returned line (remove quotes from LLDB output)
        returned_line = returned_line.strip('"')
        
        # Handle newline verification
        if expected_line.endswith('\n'):
            if not returned_line.endswith('\n'):
                return False
                
        return returned_line.rstrip('\n') == expected_line.rstrip('\n')

    def print_test_results(self, test_name):
        print(f"\n=== Test Results: {test_name} ===")
        if self.errors_found:
            print("❌ Test Failed:")
            for error in self.errors_found:
                print(f"  - {error}")
        else:
            print("✅ Test Passed")
        print("=====================\n")

    def run_test_suite(self):
        test_cases = [
            ("Basic Test", "Hello\nWorld\n"),
            ("Empty File", ""),
            ("No Newline", "Hello World"),
            ("Multiple Empty Lines", "\n\n\n"),
            ("Long Line", "A" * 1000 + "\n"),
            ("Mixed Length Lines", "Hi\nHello\nHello World\n"),
        ]

        results = []
        for name, content in test_cases:
            results.append(self.run_single_test(content, name))
        
        return all(results)
def main():
    # Compile program with debug symbols
    subprocess.run([
        "cc", "-g", 
        "get_next_line.c", 
        "test_main.c",  # Add our test harness
        "-o", "gnl_debug"
    ], check=True)
    
    # Run tests
    tester = GNLTester("./gnl_debug")
    success = tester.run_test_suite()
    
    # Final report
    print("\n=== Final Report ===")
    print("✅ All tests passed" if success else "❌ Some tests failed")
    print("==================\n")

if __name__ == "__main__":
    main()
