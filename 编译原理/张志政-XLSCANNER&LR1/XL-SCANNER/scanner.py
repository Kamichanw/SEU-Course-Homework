class Scanner:
    def __init__(self):
        # 初始化 DFA 转换表
        self.transitions = {
            0: {'+': 1, '-': 1, '*': 1, '/': 1, ';': 4, '(': 4, ')': 4, '{': 4, '}': 4, '[': 4, ']': 4, ',': 4, '.': 4,
                '=': 8,'<': 3,'>': 3,'!': 2},
        }
        for c in 'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ':
            self.transitions[0][c] = 5
            self.transitions.setdefault(5, {})[c] = 5
        for c in '0123456789':
            self.transitions[0][c] = 6
            self.transitions.setdefault(5, {})[c] = 5
            self.transitions.setdefault(6, {})[c] = 6
        # < > ! 接受=变成状态7
        self.transitions[2] = {'=': 7}
        self.transitions[3] = {'=': 7}

        # 初始化终止状态
        self.accept_states = {1,3,4,5,6,7,8}

    def scan(self, input_str):
        tokens = []
        state = 0
        token = ""
        for c in input_str:
            if c in self.transitions.get(state, {}):
                state = self.transitions[state][c]
                token += c
            else:
                if state in self.accept_states:
                    tokens.append((token, self.get_token_type(state)))
                    token = ""
                    state = 0
                    # 最长匹配
                    if c in self.transitions.get(state, {}):
                        state = self.transitions[state][c]
                        token += c
                else:
                    return "Invalid token"
        
        if state in self.accept_states:
            tokens.append((token, self.get_token_type(state)))
        else:
            # 如果某个字符无法转换到下一个状态，且当前状态不是终止状态，则说明是非法字符
            return "Invalid token"

        return tokens

    def get_token_type(self, state):
        if state == 1:
            return "Algebra Operators"
        elif state == 3:
            return "Relational Operators"
        elif state == 4:
            return "Separators"
        elif state == 5:
            return "Identifiers"
        elif state == 6:
            return "Integers"
        elif state == 7:
            return "Relational Operators"
        elif state == 8:
            return "Assignment Operator"
        else:
            return "Unknown"


if __name__ == "__main__":
    scanner = Scanner()
    input_str = input("Enter a string: ")
    result = scanner.scan(input_str)
    if isinstance(result, str):
        print(result)
    else:
        for token, token_type in result:
            print(f"Token: {token}   Type: {token_type}")