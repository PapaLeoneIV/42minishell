import subprocess

def read_test_cases(filename):
    test_cases = []
    with open(filename, 'r') as file:
        current_test = {}
        for line in file:
            line = line.strip()
            if line.startswith('input:-'):
                current_test['input'] = line[len('input:-'):].strip()
            elif line.startswith('expect:-'):
                current_test['expect'] = line[len('expect:-'):].strip()
            elif line == '-':
                if current_test:
                    test_cases.append(current_test)
                    current_test = {}
    return test_cases

def run_command(process, command):
    process.stdin.write(command + "\n")
    process.stdin.flush()
    output = []
    prompt_seen = False

    while True:
        line = process.stdout.readline().strip()
        if not line and process.poll() is not None:
            break  # If line is empty and the process has ended
        if '(Minishell)$' in line:
            if prompt_seen:
                break
            else:
                prompt_seen = True
        elif prompt_seen:
            output.append(line)


    return "\n".join(output)

def color_text(text, color):
    """ Adds ANSI color codes to the text. """
    colors = {
        'green': '\033[92m',  # Green text
        'red': '\033[91m',    # Red text
        'end': '\033[0m',     # Reset to default
    }
    return colors[color] + text + colors['end']

def main():
    test_cases = read_test_cases('test_cases.txt')
    process = subprocess.Popen(['./minishell'], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, bufsize=0)
    # Wait for minishell to be ready
    while True:
        if '(Minishell)$' in process.stdout.readline().strip():
            break

    for index, test in enumerate(test_cases, 1):
        output = run_command(process, test['input'])
        expect = test['expect']
        result = 'PASSED' if output == expect else 'FAILED'
        color = 'green' if result == 'PASSED' else 'red'
        print(f"Test {index}: {test['input']}", flush=True)
        print(f" Expect: '{expect}'", flush=True)
        print(f" Output: '{output}'", flush=True)
        print(color_text(f" Result: {result}", color), flush=True)
        print(flush=True)  # Flush the blank line for separation

    process.terminate()  # Terminate the minishell process

if __name__ == '__main__':
    main()
