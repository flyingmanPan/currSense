import gzip
import binascii
f= open("./web/upload.html", "r",encoding="utf-8")

html_content = f.read()

# Compress
# with gzip.open('./web/upload.html.gz', 'wt',encoding='utf-8') as f2:
#     f2.write(html_content)

# # Read compressed file and convert to bytes    
# with open('./web/upload.html.gz', 'rb') as f3:
#     gzipped_data = f3.read()
# print(gzipped_data[0])
# Convert bytes to hex string
# hex_data = binascii.b2a(gzipped_data).decode('utf-8')

# Format as C array
c_array = "const uint8_t serverIndex[] PROGMEM= {"
for b in gzipped_data:
    c_array+=str(b)+","
c_array+="};"

# Write to header file
with open('./html.h', 'w') as f4:   
    f4.write(c_array)