var _petQmlFiles = ["Pet1.qml", "Pet2.qml", "Pet3.qml", "Pet4.qml", "DeadPet.qml"]
var _spriteQmlFiles = ["Poop.qml"]

function createPet(petPackage, petType, parent, properties, callback) {
    var component = Qt.createComponent(petPackage + _petQmlFiles[petType])
    createObject(component, parent, properties, callback)
}

function createSprite(spritePackage, spriteType, parent, properties, callback) {
    var component = Qt.createComponent(spritePackage + _spriteQmlFiles[spriteType])
    createObject(component, parent, properties, callback)
}

function createWorld(worldLocation, parent, properties, callback) {
    var component = Qt.createComponent(worldLocation)
    createObject(component, parent, properties, callback)
}

function createObject(component, parent, properties, callback) {
    var element
    if(component.status == Component.Ready) {
        element = component.createObject(parent, properties)
        //console.log("SpriteFunctions.js: created object " + element)
        if(!!callback) callback(element)
    } else if (component.status == Component.Error) {
        //console.log("SpriteFunctions.js: error loading object:", component.errorString());
        if(!!callback) callback(null)
    } else {
        console.log("SpriteFunctions.js: component not ready")
        component.statusChanged.connect(function() {
                                            //console.log("SpriteFunctions.js: finished component")
                                            if (component.status == Component.Ready) {
                                                element = component.createObject(parent, properties)
                                                if(!!callback) callback(element)
                                            } else if (component.status == Component.Error) {
                                                //console.log("SpriteFunctions.js: error loading component:", component.errorString());
                                                if(!!callback) callback(element)
                                            }
                                        }
                                        );
    }
}

