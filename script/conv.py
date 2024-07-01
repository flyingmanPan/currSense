# Read the HTML file
with open("./web/upload.html", "r", encoding="utf-8") as f:
    html_content = f.read()

# Remove all whitespace characters
# html_content = ''.join(html_content.split())

print(html_content)
# Convert the HTML content to a C-style uint8_t array
c_array = "const char htmlContent[] PROGMEM = {"
for char in html_content:
    c_array += str(ord(char)) + ","
c_array += "};"

# Write the C-style array to a header file
with open("./html.h", "w") as f:
    f.write(c_array)