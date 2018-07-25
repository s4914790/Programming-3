TARGET = QtNGLGame
TEMPLATE = app

QT += core gui opengl

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        main.cpp \
    scene.cpp \
    camera.cpp \
    texturepack.cpp \
    actor.cpp \
    texturedmesh.cpp \
    point.cpp \
    collider.cpp \
    spherecollider.cpp \
    boxcollider.cpp \
    pawn.cpp \
    character.cpp

HEADERS += \
    glinclude.h \
    scene.h \
    camera.h \
    texturepack.h \
    actor.h \
    point.h \
    texturedmesh.h \
    collider.h \
    spherecollider.h \
    boxcollider.h \
    pawn.h \
    character.h

CONFIG += console

OBJECTS_DIR=obj
MOC_DIR=moc

OTHER_FILES+= models/* shaders/* textures/* README.md

!equals(PWD, $${OUT_PWD}){
  copydata.commands = echo "creating destination dirs" ;
  copydata.commands += mkdir -p $$OUT_PWD/models $$OUT_PWD/shaders $$OUT_PWD/textures ;
  copydata.commands += echo "copying files" ;
  copydata.commands += $(COPY_DIR) $$PWD/models/* $$OUT_PWD/models/ ;
  copydata.commands += $(COPY_DIR) $$PWD/shaders/* $$OUT_PWD/shaders/ ;
  copydata.commands += $(COPY_DIR) $$PWD/textures/* $$OUT_PWD/textures/ ;
  first.depends = $(first) copydata
  export(first.depends)
  export(copydata.commands)
  QMAKE_EXTRA_TARGETS += first copydata
}

NGLPATH=$$(NGLDIR)
isEmpty(NGLPATH){ # note brace must be here
  message("including $HOME/NGL")
  include($(HOME)/NGL/UseNGL.pri)
}
else{ # note brace must be here
  message("Using custom NGL location")
  include($(NGLDIR)/UseNGL.pri)
}

DISTFILES +=
