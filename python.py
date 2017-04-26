import sys
import os

for i in sys.argv:
	print i

###  !! use \ to continue in new line
print 'a''b',23,"k'k",'''dsa\
2332'''
#print + , to avoid endl

if True:
	print 'ok'
elif False:
	print 'no'
else:
	print '?'

while True:
	break;
else:
	pass	

#range[ )  if break no else
for i in range(0, 6, 3):
	print i
	continue
else:
	print 'ok'

#######function#########
def say(a,b=5,c=2):
	'''Some doc.

	say something'''
	print 'hello'
	global x
	print x
	return c

x=20
print say(b=2,c=2,a=3)
print say.__doc__

del x
print dir()

######list#######

shoplist = [23, 'ap']
for it in shoplist:
	print it
shoplist.append('rice')
shoplist.sort()
del shoplist[0]
print shoplist[0] #'ap'

######tuple######

###   !!  know the diff of a=(1) and a=(1,)
zoo = ('a', 'b', 'c')
new_zoo = ('A', 'B', zoo, )
print len(new_zoo)
print new_zoo
print new_zoo[2][2]

name = 'alice'
age = 23
print '%s is %d years old' % (name, age)

######map#######

ab = {
		'key1' : 'val1',
		'key2' : 'val2',
	 }
ab['key3'] = 'val3'
del ab['key2']
for name, add in ab.items():
	print name, 'to', add
if 'key1' in ab:
	print 'find %s' %ab['key1']
print ab

######seq#######

list = [0, 1, 2, 3, 4, 5]
#index
print list[1], list[-1]
#slice
print list[1:3]
print list[:]
print list[3:2]

###  !! newlist = list[:] copy ; newlist = list ref;

######str######

name = 'Swaroop'
if name.startswith('Swa'):
	if 'a' in name:
		if name.find('war') != -1:
			print 'haha'
list = ['a', 'b', 'c'+'C']
tmp = '+'
print tmp.join(list)

print os.sep

######class######

class Base:
	def __init__(self):
		print 'I am base'

class Person(Base):
	'''hello'''
	population = 0;
	def __init__(self, name): # __means private
		self.name = name
		Base.__init__(self)
	def say(self):
		print 'how are you?', self.name
	def __del__(self):
		self.__class__.population -= 1 # static
p = Person('Z')
p.say()   #change to Person.say(p)
print Person.__doc__

######IO#######

poem = '''\
		Program is fun
		Just do it yourself
'''

f = file('tmp.in', 'w')
f.write(poem)
f.close()

f = file('tmp.in')
while True:
	line = f.readline()
	if len(line) == 0:
		break
	print line,  # add , to avoid newline
f.close()

# use pickle to restore object in file

######except######

import sys

try:
	s = raw_input('Enter something -->')
except EOFError:
	print '\nWhy did you do an EOF on me?'
	sys.exit()
except:
	print '\nsomething wrong'
else:
	print 'Done'

try:
	pass
finally:
	print 'You can\'t stop me'

######Library######

import sys
# file readline close exit argv stdin/out/err

import os
# name getcwd getenv putenv listdir remove system lineseq path.split path.isfile path.isdir path.existe

######Other#######

def pow(power, *args): # **args for map
	for i in args:
		print i
	pass
pow(2,3,4)

exec 'print "hello world"'
print eval('2*3')
assert 2 > 1
