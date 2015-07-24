/****************************************************************************
** Meta object code from reading C++ file 'WidgetVideo.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/widgets/WidgetVideo.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'WidgetVideo.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_VlcWidgetVideo_t {
    QByteArrayData data[16];
    char stringdata[224];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VlcWidgetVideo_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VlcWidgetVideo_t qt_meta_stringdata_VlcWidgetVideo = {
    {
QT_MOC_LITERAL(0, 0, 14),
QT_MOC_LITERAL(1, 15, 21),
QT_MOC_LITERAL(2, 37, 0),
QT_MOC_LITERAL(3, 38, 22),
QT_MOC_LITERAL(4, 61, 19),
QT_MOC_LITERAL(5, 81, 14),
QT_MOC_LITERAL(6, 96, 10),
QT_MOC_LITERAL(7, 107, 5),
QT_MOC_LITERAL(8, 113, 12),
QT_MOC_LITERAL(9, 126, 16),
QT_MOC_LITERAL(10, 143, 18),
QT_MOC_LITERAL(11, 162, 13),
QT_MOC_LITERAL(12, 176, 8),
QT_MOC_LITERAL(13, 185, 10),
QT_MOC_LITERAL(14, 196, 5),
QT_MOC_LITERAL(15, 202, 21)
    },
    "VlcWidgetVideo\0enableDefaultSettings\0"
    "\0enablePreviousSettings\0initDefaultSettings\0"
    "setAspectRatio\0Vlc::Ratio\0ratio\0"
    "setCropRatio\0setDeinterlacing\0"
    "Vlc::Deinterlacing\0deinterlacing\0"
    "setScale\0Vlc::Scale\0scale\0"
    "applyPreviousSettings"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VlcWidgetVideo[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x0a /* Public */,
       3,    0,   55,    2, 0x0a /* Public */,
       4,    0,   56,    2, 0x0a /* Public */,
       5,    1,   57,    2, 0x0a /* Public */,
       8,    1,   60,    2, 0x0a /* Public */,
       9,    1,   63,    2, 0x0a /* Public */,
      12,    1,   66,    2, 0x0a /* Public */,
      15,    0,   69,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void, 0x80000000 | 13,   14,
    QMetaType::Void,

       0        // eod
};

void VlcWidgetVideo::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        VlcWidgetVideo *_t = static_cast<VlcWidgetVideo *>(_o);
        switch (_id) {
        case 0: _t->enableDefaultSettings(); break;
        case 1: _t->enablePreviousSettings(); break;
        case 2: _t->initDefaultSettings(); break;
        case 3: _t->setAspectRatio((*reinterpret_cast< const Vlc::Ratio(*)>(_a[1]))); break;
        case 4: _t->setCropRatio((*reinterpret_cast< const Vlc::Ratio(*)>(_a[1]))); break;
        case 5: _t->setDeinterlacing((*reinterpret_cast< const Vlc::Deinterlacing(*)>(_a[1]))); break;
        case 6: _t->setScale((*reinterpret_cast< const Vlc::Scale(*)>(_a[1]))); break;
        case 7: _t->applyPreviousSettings(); break;
        default: ;
        }
    }
}

const QMetaObject VlcWidgetVideo::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_VlcWidgetVideo.data,
      qt_meta_data_VlcWidgetVideo,  qt_static_metacall, 0, 0}
};


const QMetaObject *VlcWidgetVideo::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VlcWidgetVideo::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_VlcWidgetVideo.stringdata))
        return static_cast<void*>(const_cast< VlcWidgetVideo*>(this));
    if (!strcmp(_clname, "VlcVideoDelegate"))
        return static_cast< VlcVideoDelegate*>(const_cast< VlcWidgetVideo*>(this));
    return QFrame::qt_metacast(_clname);
}

int VlcWidgetVideo::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
