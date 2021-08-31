Array.prototype.distinctPush = function (obj, proprety) {
  let arr = this;
  let index = -1;
  arr.forEach((v, i, a) => {
    if (v[proprety] == obj[proprety]) {
      index = i;
    }
  });
  return index === -1 ? this.push(obj) : this.splice(index, 1, obj);
}
Array.prototype.getIndexByProprety = function (val, proprety) {
  let arr = this;
  let index = -1;
  arr.forEach((v, i, a) => {
    if (v[proprety] == val) {
      index = i;
    }
  });
  return index;
}
Array.prototype.getObjByProprety = function (val, proprety) {
  let arr = this;
  let obj;
  arr.forEach((v, i, a) => {
    if (v[proprety] === val) {
      obj = v;
    }
  });
  return obj;
}
Array.prototype.deteleObjByProprety = function (val, proprety) {
  let arr = this;
  let index = -1;
  arr.forEach((v, i, a) => {
    if (v[proprety] == val) {
      index = i;
    }
  });
  this.splice(index, 1);
  return this;
}