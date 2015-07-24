/****************************************************************************
** Meta object code from reading C++ file 'MediaListPlayer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/core/MediaListPlayer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MediaListPlayer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_VlcMediaListPlayer_t {
    QByteArrayData data[12];
    char stringdata[100];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VlcMediaListPlayer_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VlcMediaListPlayer_t qt_meta_stringdata_VlcMediaListPlayer = {
    {
QT_MOC_LITERAL(0, 0, 18),
QT_MOC_LITERAL(1, 19, 6),
QT_MOC_LITERAL(2, 26, 0),
QT_MOC_LITERAL(3, 27, 11),
QT_MOC_LITERAL(4, 39, 15),
QT_MOC_LITERAL(5, 55, 7),
QT_MOC_LITERAL(6, 63, 6),
QT_MOC_LITERAL(7, 70, 5),
QT_MOC_LITERAL(8, 76, 4),
QT_MOC_LITERAL(9, 81, 4),
QT_MOC_LITERAL(10, 86, 8),
QT_MOC_LITERAL(11, 95, 4)
    },
    "VlcMediaListPlayer\0played\0\0nextItemSet\0"
    "libvlc_media_t*\0stopped\0itemAt\0index\0"
    "next\0play\0previous\0stop"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VlcMediaListPlayer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x06 /* Public */,
       3,    1,   55,    2, 0x06 /* Public */,
       5,    0,   58,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   59,    2, 0x0a /* Public */,
       8,    0,   62,    2, 0x0a /* Public */,
       9,    0,   63,    2, 0x0a /* Public */,
      10,    0,   64,    2, 0x0a /* Public */,
      11,    0,   65,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    2,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void VlcMediaListPlayer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        VlcMediaListPlayer *_t = static_cast<VlcMediaListPlayer *>(_o);
        switch (_id) {
        case 0: _t->played(); break;
        case 1: _t->nextItemSet((*reinterpret_cast< libvlc_media_t*(*)>(_a[1]))); break;
        case 2: _t->stopped(); break;
        case 3: _t->itemAt((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->next(); break;
        case 5: _t->play(); break;
        case 6: _t->previous(); break;
        case 7: _t->stop(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (VlcMediaListPlayer::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VlcMediaListPlayer::played)) {
                *result = 0;
            }
        }
        {
            typedef void (VlcMediaListPlayer::*_t)(libvlc_media_t * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VlcMediaListPlayer::nextItemSet)) {
                *result = 1;
            }
        }
        {
            typedef void (VlcMediaListPlayer::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VlcMediaListPlayer::stopped)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject VlcMediaListPlayer::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_VlcMediaListPlayer.data,
      qt_meta_data_VlcMediaListPlayer,  qt_static_metacall, 0, 0}
};


const QMetaObject *VlcMediaListPlayer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VlcMediaListPlayer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_VlcMediaListPlayer.stringdata))
        return static_cast<void*>(const_cast< VlcMediaListPlayer*>(this));
    return QObject::qt_metacast(_clname);
}

int VlcMediaListPlayer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void VlcMediaListPlayer::played()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void VlcMediaListPlayer::nextItemSet(libvlc_media_t * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void VlcMediaListPlayer::stopped()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
QT_END_MOC_NAMESPACE
