def hexprint(input_data, n):
    print("          1  2  3  4  5  6  7  8  9  0")
    for i, elem in enumerate(input_data[:n]):
        if (i+1)%10 != 0:
            if (i+1)%10 != 1:
                print(format(elem, '02x'), end=" ")
            else:
                print("%08d" %((i+1)//10), format(elem, '02x'), end=" ")
        else:
            print(format(elem, '02x'))
    print()

def hexcharprint(input_data, n):
    print("          1  2  3  4  5  6  7  8  9  0")
    for i, elem in enumerate(input_data[:n]):
        output_char = format(elem, '02x')
        decimal_char = int(output_char, 16)
        if (i+1)%10 != 0:
            if (i+1)%10 != 1:
                if (decimal_char > 31) & (decimal_char < 127):
                   print(" %s" %chr(decimal_char), end=" ")
                else:
                   print(output_char, end=" ")
            else:
                if (decimal_char > 31) & (decimal_char < 127):
                   print("%08d" %((i+1)//10)," %s" %chr(decimal_char), end=" ")
                else:
                   print("%08d" %((i+1)//10),output_char, end=" ")
        else:
            if (decimal_char > 31) & (decimal_char < 127):
                print(" %s" %chr(decimal_char))
            else:
                print(output_char)
    print()
