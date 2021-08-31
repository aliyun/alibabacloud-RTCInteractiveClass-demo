// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#ifndef DPS_DEFINE_H
#define DPS_DEFINE_H
#if defined(DPS_EXPORT)
#define DPS_DECL __attribute__((visibility("default")))
#else
#define DPS_DECL
#endif
#endif