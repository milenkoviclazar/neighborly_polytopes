def get_content(input_filename):
    with open(input_filename) as f:
        content = f.readlines()
    content = [x.strip() for x in content]
    return content