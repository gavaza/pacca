# On windows, a shared object is a .dll
win32: SONAME=dll
macx:  SONAME=dylib
else:  SONAME=so

# This function sets up the dependencies for libraries that are built with
# this project.  Specify the libraries you need to depend on in the variable
# DEPENDENCY_LIBRARIES and this will add
for(dep, DEPENDENCY_LIBRARIES) {
    message($$TARGET depends on $$dep ($${DESTDIR}/../lib/$${dep}.$${SONAME}))
    LIBS += $${DESTDIR}/../lib/lib$${dep}.$${SONAME}
    PRE_TARGETDEPS += $${DESTDIR}/../lib/lib$${dep}.$${SONAME}
}
