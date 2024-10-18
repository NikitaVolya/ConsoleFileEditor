
def MySum(*args):
     rep = 0
     for n in args:
          rep += n
     return rep


def main():
     a = int(input("a: "))
     b = int(input("b: "))
     print("Your sum is", MySum(a, b))
     name = input("Your name: ")
     print(name)

if __name__ == "__main__":
     main()
