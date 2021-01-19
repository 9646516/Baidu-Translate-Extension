# Textractor 的百度翻译插件

基于百度的通用翻译API。抱歉没有编译好的版本，请自行编译。

## 使用方法

- 先去[百度翻译开放平台](http://api.fanyi.baidu.com/product/11)申请一个QPS高达1而且完全免费的标准版API,并且得到APP ID和Key
- 修改`src\Extension.cpp`中的appID和appKey
- 用`MSVC`编译得到dll,在Textractor中挂载即可

