// Copyright (c) 2019 The Alibaba DingTalk Authors. All rights reserved.

#import "AIMMsgAudioContent.h"
#import "AIMMsgCustomContent.h"
#import "AIMMsgFileContent.h"
#import "AIMMsgGeoContent.h"
#import "AIMMsgImageContent.h"
#import "AIMMsgVideoContent.h"
#import "AIMPubMsgStructContent.h"
#import "AIMPubMsgTextContent.h"
#import <Foundation/Foundation.h>

@interface AIMPubMsgSimpleContent : NSObject
- (nonnull instancetype)
    initWithTextContent:(nonnull AIMPubMsgTextContent *)textContent
           imageContent:(nonnull AIMMsgImageContent *)imageContent
           audioContent:(nonnull AIMMsgAudioContent *)audioContent
           videoContent:(nonnull AIMMsgVideoContent *)videoContent
             geoContent:(nonnull AIMMsgGeoContent *)geoContent
          customContent:(nonnull AIMMsgCustomContent *)customContent
          structContent:(nonnull AIMPubMsgStructContent *)structContent
            fileContent:(nonnull AIMMsgFileContent *)fileContent;
+ (nonnull instancetype)
    AIMPubMsgSimpleContentWithTextContent:
        (nonnull AIMPubMsgTextContent *)textContent
                             imageContent:
                                 (nonnull AIMMsgImageContent *)imageContent
                             audioContent:
                                 (nonnull AIMMsgAudioContent *)audioContent
                             videoContent:
                                 (nonnull AIMMsgVideoContent *)videoContent
                               geoContent:(nonnull AIMMsgGeoContent *)geoContent
                            customContent:
                                (nonnull AIMMsgCustomContent *)customContent
                            structContent:
                                (nonnull AIMPubMsgStructContent *)structContent
                              fileContent:
                                  (nonnull AIMMsgFileContent *)fileContent;

@property(nonatomic, nonnull) AIMPubMsgTextContent *textContent;

@property(nonatomic, nonnull) AIMMsgImageContent *imageContent;

@property(nonatomic, nonnull) AIMMsgAudioContent *audioContent;

@property(nonatomic, nonnull) AIMMsgVideoContent *videoContent;

@property(nonatomic, nonnull) AIMMsgGeoContent *geoContent;

@property(nonatomic, nonnull) AIMMsgCustomContent *customContent;

@property(nonatomic, nonnull) AIMPubMsgStructContent *structContent;

@property(nonatomic, nonnull) AIMMsgFileContent *fileContent;

@end
