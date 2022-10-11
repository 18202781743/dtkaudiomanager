// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#define DAUDIOMANAGER_NAMESPACE Dtk::AudioManager

#define DAUDIOMANAGER_USE_NAMESPACE using namespace DAUDIOMANAGER_NAMESPACE;

#define DAUDIOMANAGER_BEGIN_NAMESPACE namespace Dtk { namespace AudioManager {
#define DAUDIOMANAGER_END_NAMESPACE }}

#if defined(DTK_STATIC_LIB)
#  define LIBDTKAUDIOMANAGERSHARED_EXPORT
#else
#if defined(LIBDTKAUDIOMANAGER_LIBRARY)
#  define LIBDTKAUDIOMANAGERSHARED_EXPORT Q_DECL_EXPORT
#else
#  define LIBDTKAUDIOMANAGERSHARED_EXPORT Q_DECL_IMPORT
#endif
#endif
