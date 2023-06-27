// const MyObject = require("bindings")("myObject.node")
const addon = require("./build/Release/myObject")

const a = new addon.MyObject(23);
console.log(a);
console.log(a.plusOne());


const Map = require("./build/Release/map");
let res = Map(["芙兰朵露", "蛋花汤", "南瓜饼"], function() { return arguments; });
console.log(res);

const { get, div } = require("./build/Release/get");
const res1 = get({"a": "success getton"}, "a");
console.log(`=== try_catch_exception.node method get res1: ${res1}`);

try {
  const res2 = get(null, "a");
  console.log(`=== try_catch_exception.node method get res2: ${res2}`);
} catch(err) {
  console.log(err.message);
}

const res3 = div(4, 2);
console.log(`=== try_catch_exception.node method div res3: ${res3}`);
try {
  const res4 = div(4, 0);
  console.log(`=== try_catch_exception.node method div res4: ${res4}`);
} catch (err) {
  console.log(err.message);
}


const { hello } = require("./build/Release/hello");
const res5 = hello("zhangsan");
console.log(`hello method's result res5: ${res5}`);


const { add } = require('./build/Release/add');
const res6 = add(3, 4);
console.log(`add method's result res6: ${res6}`);

try {
  const res7 = add(3, "4");
  console.log(`add method's result res7: ${res7}`);
} catch (err) {
  console.log(err.message);
}

try {
  const res8 = add(3);
  console.log(`add method's result res8: ${res8}`);
} catch (err) {
  console.log(err.message);
}

const {runCallback} = require('./build/Release/runCallback');
const res9 = runCallback("zhangsan2", console.log);
console.log(`res9: ${res9}`);

const { createObj} = require('./build/Release/createObj');
const res10 = createObj("lisi");
console.log(`res10: ${JSON.stringify(res10)}`);

const {createFunc} = require('./build/Release/createFunc');
const func = createFunc();
const res11 = func();
console.log(`res11: ${res11}`);

const { Echo } = require('./build/Release/echo');
Echo('112313');
Echo('================================================================');
Echo(undefined);
Echo(null);
try {
  Echo();
} catch (err) {
  console.log(`Echo() throw an exception: ${err}`);
}

const { nmap } = require('./build/Release/nmap');
const res12 = nmap([1,3,4], (i) => { console.log(i); return i; });
console.log(`nmap res12: ${res12}`);

