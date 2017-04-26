@interface test : NSObject

+-(int) sum: (int) a ID2: (int) b;
@property testId (getter=anothername);
	// [t setTestId: xxx]
	// [t testId]
@property BOOL finished;

@end

@implementation test

+-(int) sum: (int) a ID2: (int) b
{
	return a + b;
}

@end

NSLog(@"sad")
NSLog(@"%s", str);
test *t = [[test alloc]init] == [test new]
int ret = [test sum: a ID2 b];

[t setStr: @"ok"]
t.str = @"no";
NSString *tmp = t.str;

@property (atomic:default) int age;
self.age = [self age] = _age; -(int) age{ return _age;}

{
	int tmpVar; // protected
}

- (id) init {
	self = [super init];
	if (self) {
		
	}
	return self;
}

all object in oc are dynamic alloc in heap
if one object obtain another , we say first has string references to second
if one which no other string references to them whill be deallocated

if strong reference forms circle, problem happens. then we can use weak declarations
ex. @property (weak) id some;  
	NSObject *__weak var;
NSObject * __weak som = [[NSObject alloc] init];  // false som will be nil

__unsafe_unretained == __weak // weak will be set to nil while unsafe won't

@property (copy) NSString *str; // won't be changed

NSMutableString *str1 = [NSMutableString stringWithString:@"John"];
NSMutableString *str2 = str1;
[str1 appendString:@"ok"];
NSLog(@"%@ %@", str1, str2);
// both Johnok
str2 = [str1 copy];
// str2 will be John

@interface/implementation class (categoryName) // insert new method

@protocol myProtocol <NSObject>
@required (default)

@optional

@end

@interface MyClass : NSObject <MyProtocol, My2, My3>
implement required

test protocal or optional method while use;
