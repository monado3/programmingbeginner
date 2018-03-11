urldict={}

table62=[str(i) for i in range(0,10)]
for i in range(ord('a'),ord('z')+1):
    table62.append(chr(i))
for i in range(ord('A'),ord('Z')+1):
    table62.append(chr(i))

def add_short_url(link):
    global urldict
    hash=abs(link.__hash__())
    while True:
        shorten=""
        quotient=hash
        while quotient!=0:
            remainder=quotient%62
            quotient=quotient//62
            shorten= table62[remainder] + shorten
        if shorten[0]=='0' and len(shorten)!=1:
            shorten=shorten[1:]
        if shorten in urldict.keys():
            hash+=1
        else:
            urldict[shorten]=link
            print(shorten)
            return shorten

def get_long_url(shorten):
    print(urldict[shorten])


test=add_short_url("http://hello.com")
get_long_url(test)