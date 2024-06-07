import subprocess
import os

def read_test_cases(filename):
    test_cases = []
    with open(filename, 'r') as file:
        current_test = {}
        for line in file:
            line = line.strip()
            if line.startswith('input:-'):
                current_test['input'] = line[len('input:-'):].strip()
            elif line == '-':
                if current_test:
                    test_cases.append(current_test)
                    current_test = {}
    return test_cases

def run_valgrind(command):
    path_to_minishell = '../minishell'
    valgrind_command = [
        'valgrind', '--suppressions=ignore_readline.txt',
        '--leak-check=full', '--track-origins=yes', path_to_minishell
    ]
    process = subprocess.Popen(
        valgrind_command,
        stdin=subprocess.PIPE,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True,
    )
    process.stdin.write(command + "\n")
    process.stdin.flush()
    _, stderr = process.communicate()
    return stderr

def main():
    output_directory = 'LEAK_test_outputs'  # Directory to store all output files
    if not os.path.exists(output_directory):
        os.makedirs(output_directory)  # Create the directory if it does not exist

    test_cases = read_test_cases('test_cases_leak.txt')
    for index, test in enumerate(test_cases, 1):
        log_file = os.path.join(output_directory, f'memory_leak_report_{index}.txt')
        with open(log_file, 'w') as file:
            file.write("Test Input: " + test['input'] + "\n\n")
            errors = run_valgrind(test['input'])
            file.write(errors)
        print(f"Test {index}: {test['input']} processed. Errors logged in {log_file}.")

if __name__ == '__main__':
    main()
