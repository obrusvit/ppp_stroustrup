read_from = open('lorem_ipsum_500000_paragraphs.txt', 'r')
write_to = open('lorem_test_python.txt', 'w')
for line in read_from:
    write_to.write(line)
read_from.close()
write_to.close()
