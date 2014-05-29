.pragma library

var _privs = {}

function register(key) {
    var hash = key.toString()
    var o = _privs[key];
    if(!o) {
        o = {}
        _privs[key] = o;
    }
    return o;
}
