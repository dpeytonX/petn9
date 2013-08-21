var _petQmlFiles = ["Pet1.qml", "Pet2.qml", "Pet3.qml", "Pet4.qml"]

function createPet(petPackage, petType, parent, properties, callback) {
    var component = Qt.createComponent(petPackage + _petQmlFiles[petType])
    var petItem
    if(component.status == Component.Ready) {
        petItem = component.createObject(parent, properties)
        console.log("SpriteFunctions.js: created pet " + petItem)
        if(!!callback) callback(petItem)
    }else if (component.status == Component.Error) {
        console.log("SpriteFunctions.js: error loading pet:", component.errorString());
        if(!!callback) callback(null)
    } else {
        console.log("SpriteFunctions.js: pet not ready")
        component.statusChanged.connect(function() {
                                            console.log("SpriteFunctions.js: finish pet")
                                            if (component.status == Component.Ready) {
                                                petItem = component.createObject(parent, properties)
                                                if(!!callback) callback(petItem)
                                            } else if (worldObject.status == Component.Error) {
                                                console.log("SpriteFunctions.js: error loading pet:", component.errorString());
                                                if(!!callback) callback(petItem)
                                            }
                                        }
                                        );
    }
}
