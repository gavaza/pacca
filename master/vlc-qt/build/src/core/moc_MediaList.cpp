/****************************************************************************
** Meta object code from reading C++ file 'MediaList.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/core/MediaList.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MediaList.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_VlcMediaList_t {
    QByteArrayData data[7];
    char stringdata[79];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VlcMediaList_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VlcMediaList_t qt_meta_stringdata_VlcMediaList = {
    {
QT_MOC_LITERAL(0, 0, 12),
QT_MOC_LITERAL(1, 13, 9),
QT_MOC_LITERAL(2, 23, 0),
QT_MOC_LITERAL(3, 24, 15),
QT_MOC_LITERAL(4, 40, 11),
QT_MOC_LITERAL(5, 52, 11),
QT_MOC_LITERAL(6, 64, 14)
    },
    "VlcMediaList\0itemAdded\0\0libvlc_media_t*\0"
    "willAddItem\0itemDeleted\0willDeleteItem"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VlcMediaList[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   34,    2, 0x06 /* Public */,
       4,    2,   39,    2, 0x06 /* Public */,
       5,    2,   44,    2, 0x06 /* Public */,
       6,    2,   49,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    2,    2,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    2,    2,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    2,    2,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    2,    2,

       0        // eod
};

void VlcMediaList::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        VlcMediaList *_t = static_cast<VlcMediaList *>(_o);
        switch (_id) {
        case 0: _t->itemAdded((*reinterpret_cast< libvlc_media_t*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->willAddItem((*reinterpret_cast< libvlc_media_t*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->itemDeleted((*reinterpret_cast< libvlc_media_t*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->willDeleteItem((*reinterpret_cast< libvlc_media_t*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (VlcMediaList::*_t)(libvlc_media_t * , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VlcMediaList::itemAdded)) {
                *result = 0;
            }
        }
        {
            typedef void (VlcMediaList::*_t)(libvlc_media_t * , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VlcMediaList::willAddItem)) {
                *result = 1;
            }
        }
        {
            typedef void (VlcMediaList::*_t)(libvlc_media_t * , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VlcMediaList::itemDeleted)) {
                *result = 2;
            }
        }
        {
            typedef void (VlcMediaList::*_t)(libvlc_media_t * , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VlcMediaList::willDeleteItem)) {
                *result = 3;
            }
        }
    }
}

const QMetaObject VlcMediaList::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_VlcMediaList.data,
      qt_meta_data_VlcMediaList,  qt_static_metacall, 0, 0}
};


const QMetaObject *VlcMediaList::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VlcMediaList::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_VlcMediaList.stringdata))
        return static_cast<void*>(const_cast< VlcMediaList*>(this));
    return QObject::qt_metacast(_clname);
}

int VlcMediaList::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void VlcMediaList::itemAdded(libvlc_media_t * _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void VlcMediaList::willAddItem(libvlc_media_t * _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void VlcMediaList::itemDeleted(libvlc_media_t * _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void VlcMediaList::willDeleteItem(libvlc_media_t * _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
