//
//  ZFPlayerView.h
//
// Copyright (c) 2016年 任子丰 ( http://github.com/renzifeng )
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#import <UIKit/UIKit.h>

// 返回按钮的block
typedef void(^ZFPlayerBackCallBack)(void);
// 下载按钮的回调
typedef void(^ZFDownloadCallBack)(NSString *urlStr);

// playerLayer的填充模式（默认：等比例填充，直到一个维度到达区域边界）
typedef NS_ENUM(NSInteger, ZFPlayerLayerGravity) {
    ZFPlayerLayerGravityResize,           // 非均匀模式。两个维度完全填充至整个视图区域
    ZFPlayerLayerGravityResizeAspect,     // 等比例填充，直到一个维度到达区域边界
    ZFPlayerLayerGravityResizeAspectFill  // 等比例填充，直到填充满整个视图区域，其中一个维度的部分区域会被裁剪
};


typedef NS_ENUM(NSInteger, ZFPlayerCellVideoOutPoint) {
    ZFPlayerCellVideoOutPointRightBottom,    // 超出屏幕 时 播放窗口位置 左下
    ZFPlayerCellVideoOutPointRightTop,       // 超出屏幕 时 播放窗口位置 右上
};

// 播放器的几种状态
typedef NS_ENUM(NSInteger, ZFPlayerState) {
    ZFPlayerStateFailed,     // 播放失败
    ZFPlayerStateBuffering,  // 缓冲中
    ZFPlayerStatePlaying,    // 播放中
    ZFPlayerStateStopped,    // 停止播放
    ZFPlayerStatePause       // 暂停播放
};

@interface ZFPlayerView : UIView

- (instancetype) init;

/** 视频URL */
@property (nonatomic, strong) NSURL                *videoURL;
/** 视频标题 */
@property (nonatomic, strong) NSString             *title;
/** 视频URL的数组 */
@property (nonatomic, strong) NSArray              *videoURLArray;
/** 返回按钮Block */
@property (nonatomic, copy  ) ZFPlayerBackCallBack goBackBlock;
@property (nonatomic, copy  ) ZFDownloadCallBack   downloadBlock;
/** 设置playerLayer的填充模式 */
@property (nonatomic, assign) ZFPlayerLayerGravity playerLayerGravity;
/** 是否有下载功能(默认是关闭) */
@property (nonatomic, assign) BOOL                 hasDownload;
/** 切换分辨率传的字典(key:分辨率名称，value：分辨率url) */
@property (nonatomic, strong) NSDictionary         *resolutionDic;
/** 从xx秒开始播放视频跳转 */
@property (nonatomic, assign) NSInteger            seekTime;
/** 播放前占位图片的名称，不设置就显示默认占位图（需要在设置视频URL之前设置） */
@property (nonatomic, copy  ) NSString             *placeholderImageName;
@property (nonatomic, copy  ) UIImage              *placeholderImage;
/** 是否被用户暂停 */
@property (nonatomic, assign, readonly) BOOL       isPauseByUser;
/** 播发器的几种状态 */
@property (nonatomic, assign, readonly) ZFPlayerState   state;

#pragma mark CellVideo
/** Cell模式的时候超出屏幕，是否在屏幕右上播放 */
@property (nonatomic, assign) ZFPlayerCellVideoOutPoint cellVideoOutPoint;
/** 默认 NO，在设置视频 URL 之前设置有效 */
@property (nonatomic, assign) BOOL  hiddenCloseBtnWhenCellVideo;
/** 默认 NO，Cell模式的时候超出屏幕，是否自动移除 */
@property (nonatomic, assign) BOOL  autoRemoveWhemCellVideoOut;
#pragma mark

/**
 *  自动播放，默认不自动播放
 */
- (void)autoPlayTheVideo;

/**
 *  取消延时隐藏controlView的方法,在ViewController的delloc方法中调用
 *  用于解决：刚打开视频播放器，就关闭该页面，maskView的延时隐藏还未执行。
 */
- (void)cancelAutoFadeOutControlBar;

/**
 *  单例，用于列表cell上多个视频
 *
 *  @return ZFPlayer
 */
+ (instancetype)sharedPlayerView;

/**
 *  player添加到cell上
 *
 *  @param cell 添加player的cellImageView
 */
- (void)addPlayerToCellImageView:(UIImageView *)imageView;

/**
 *  重置player
 */
- (void)resetPlayer;

/**
 *  在当前页面，设置新的Player的URL调用此方法
 */
- (void)resetToPlayNewURL;

/**
 *  播放
 */
- (void)play;

/**
 * 暂停
 */
- (void)pause;

/** 设置URL的setter方法 */
- (void)setVideoURL:(NSURL *)videoURL;

/**
 *  用于cell上播放player
 *
 *  @param videoURL  视频的URL
 *  @param tableView tableView
 *  @param indexPath indexPath
 *  @param ImageViewTag ImageViewTag
 */
- (void)setVideoURL:(NSURL *)videoURL
      withTableView:(UITableView *)tableView
        AtIndexPath:(NSIndexPath *)indexPath
   withImageViewTag:(NSInteger)tag;


@end
