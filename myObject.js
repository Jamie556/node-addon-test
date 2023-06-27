function MyObject(value) {
  this._value = value;
}

MyObject.prototype.plusOne = function() {
  return ++this._value;
}
