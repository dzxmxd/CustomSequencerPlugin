### 自定义 Sequencer 轨道开发
模仿 UE 内轨道逻辑，开发自定义 Sequencer 轨道，并完成其预览逻辑。




#### 博客地址：
[自定义 Sequencer 轨道开发](https://santa.wang/custom_sequencer_track_dev/)

#### 使用方法
将 CustomSequencerPlugin 目录及目录下文件放置于工程或引擎 Plugin 目录，运行即可。

笔者使用 UE 5.0.2 开发。

#### 示例效果：
![](./img/CustomSequencer.gif)

启动插件后，会弹出一个 Viewport 并弹出系统的 Sequencer 界面，如果 Sequencer 界面未弹出，也可能吸附在了主界面上，可以回到 UE 主界面查看。轨道的效果与系统基本一致，此处仅演示预览效果，在本文的预览逻辑示例代码中，TestPreviewTrack 持有一个相机，预览时会使用当前 EValuate 位置的时间对此相机的高度进行修正。按照系统方法昂贵的计算在 Evaluate 方法中完成的逻辑，我们在 Evaluate 方法处，使用这一时间计算了相机应该设置的高度，并使用此高度创建了自定义 Token 类的实例。自定义的 Token 类中保存了 TestPreviewSection 与 一个 FVector 类型的新坐标，并存入了真正将要执行的 Token 队列，在 Execute 即真正的预览执行时，使用构造时的入参设置了相机的 Location。
这样就完成了对相机高度修正的预览效果。最终表现为，相机高度随着播放位置变化。

