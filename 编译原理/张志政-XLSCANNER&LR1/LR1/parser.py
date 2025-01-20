class Parser:
    def __init__(self):
        self.action_table = {
            0: {'(': 's2', 'int': 's3', 'id': 's4'},
            1: {'$': 'SUCC', ';': 's9', 'op': 's10'},
            2: {'(': 's6', 'int': 's7', 'id': 's8'},
            3: {'op': 'r3', '$': 'r3', ';': 'r3'},
            4: {'op': 'r4', '$': 'r4', ';': 'r4'},
            5: {'op': 's12', ')': 's11', ';': 's14'},
            6: {'(': 's6', 'int': 's7', 'id': 's8'},
            7: {'op': 'r3', ')': 'r3', '$': 'r3', ';': 'r3'},
            8: {'op': 'r4', ')': 'r4', '$': 'r4', ';': 'r4'},
            9: {'op': 'r5', '$': 'r5', ';': 'r5'},
            10: {'(': 's2', 'int': 's3', 'id': 's4'},
            11: {'op': 'r2', '$': 'r2', ';': 'r2'},
            12: {'int': 's7', 'id': 's8'},
            13: {'op': 's12', ')': 's17', ';': 's14'},
            14: {'op': 'r5', ')': 'r5', '$': 'r5', ';': 'r5'},
            15: {'op': 'r1', '$': 'r1', ';': 's9'},
            16: {'op': 'r1', ')': 'r1', '$': 'r1', ';': 's14'},
            17: {'op': 'r2', ')': 'r2', '$': 'r2', ';': 'r2'}
        }
        self.goto_table = {
            0: {'S': 1},
            2: {'S': 5},
            6: {'S': 13},
            10: {'S': 15},
            12: {'S': 16},
            13: {'S': 14},
        }
        self.grammar = [
            ('S', 'S op S'),#空格是为了区分两个字符）
            ('S', '( S )'),
            ('S', 'int'),
            ('S', 'id'),
            ('S', 'S ;')
        ]

    def parse(self, tokens):
        stack = [0]
        index = 0
        while True:
            state = stack[-1]
            token = tokens[index] if index < len(tokens) else '$'
            action = self.action_table[state].get(token)
            print(f"State: {state}, Token: {token}, Action: {action}")
            if action is None:
                raise SyntaxError(f"Unexpected token: {token}")
            if action.startswith('s'):
                stack.append(int(action[1:]))
                index += 1
            elif action.startswith('r'):
                rule = self.grammar[int(action[1:]) - 1]
                for _ in range(len(rule[1].split())):
                    stack.pop()
                stack.append(self.goto_table[stack[-1]][rule[0]])
            elif action == 'SUCC':
                print("Parsing succeeded!")
                return
            else:
                raise SyntaxError(f"Invalid action: {action}")


tokens_list = [
    ['int', 'op', 'int', '$'],  # 简单的表达式
    ['id', 'op', 'id', '$'],    # 标识符表达式
    ['(', 'int', 'op', 'int', ')', '$'],  # 带括号的表达式
    ['int', ';', 'int', '$'],   # 带分号的错误表达式
    ['id', ';','op', 'int', '$'],  # 复杂表达式
    ['(', 'int', ')', 'op', 'int', ';','$'],  # 状态15碰到op的情况
]

parser = Parser()
for tokens in tokens_list:
    print(f"Parsing tokens: {tokens}")
    try:
        parser.parse(tokens)
    except SyntaxError as e:
        print(e)
    print()