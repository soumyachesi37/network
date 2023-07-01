# Parity Generator
def parity_generator(data, parity):
    ones_count = data.count('1')
    if parity == 'even':
        if ones_count % 2 == 0:
            parity_bit = '0'
        else:
            parity_bit = '1'
    elif parity == 'odd':
        if ones_count % 2 == 0:
            parity_bit = '1'
        else:
            parity_bit = '0'
    else:
        print("Invalid parity type")
        return None
    return data + parity_bit


# Parity Checker
def parity_checker(received_data, parity):
    ones_count = received_data.count('1')
    if parity == 'even':
        if ones_count % 2 == 0:
            parity_bit = '0'
        else:
            parity_bit = '1'
    elif parity == 'odd':
        if ones_count % 2 == 0:
            parity_bit = '1'
        else:
            parity_bit = '0'
    else:
        print("Invalid parity type")
        return None
    if received_data[-1] == parity_bit:
        return received_data[:-1]
    else:
        return "Error: Parity bit does not match the data"

# Example Usage
data = '1010101'
parity = 'even'
generated_data = parity_generator(data, parity)
print("Generated data:", generated_data)

received_data = '1010100'
received_parity = 'even'
checked_data = parity_checker(received_data, received_parity)
print("Checked data:", checked_data)
