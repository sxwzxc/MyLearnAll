<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE TS>
<TS version="2.1" language="zh_CN" sourcelanguage="zh_CN">
<context>
    <name>MainWindow</name>
    <message>
        <location filename="mainwindow.ui" line="14"/>
        <source>MainWindow</source>
        <translation></translation>
    </message>
    <message>
        <location filename="mainwindow.ui" line="27"/>
        <source>为UAT添加内网能力</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="mainwindow.ui" line="40"/>
        <source>收回能力</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="mainwindow.ui" line="53"/>
        <source>打开网络设置</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="mainwindow.ui" line="66"/>
        <source>切换为UAT网络</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="mainwindow.ui" line="79"/>
        <source>切换为内网网络</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="mainwindow.ui" line="92"/>
        <source>请将内网网卡更名为：以太网</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="mainwindow.ui" line="105"/>
        <source>解析内网可访问但UAT下无法访问的网站（暂无效）</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="mainwindow.cpp" line="37"/>
        <location filename="mainwindow.cpp" line="106"/>
        <source>beginMark</source>
        <translation># ********** Begin__Please DO NOT Change Anything**********</translation>
    </message>
    <message>
        <location filename="mainwindow.cpp" line="38"/>
        <location filename="mainwindow.cpp" line="39"/>
        <location filename="mainwindow.cpp" line="131"/>
        <source>endMark</source>
        <translation># ********** End__Please DO NOT Change Anything**********</translation>
    </message>
    <message>
        <location filename="mainwindow.cpp" line="47"/>
        <location filename="mainwindow.cpp" line="100"/>
        <source>No Permission</source>
        <translation>权限不足！请检查是否授予管理员权限，以及杀毒软件是否拦截。</translation>
    </message>
    <message>
        <location filename="mainwindow.cpp" line="61"/>
        <location filename="mainwindow.cpp" line="88"/>
        <source>UATCmd</source>
        <translation>netsh interface ip set dnsservers name = &quot;以太网&quot; static 52.83.74.116 primary</translation>
    </message>
    <message>
        <location filename="mainwindow.cpp" line="64"/>
        <location filename="mainwindow.cpp" line="77"/>
        <location filename="mainwindow.cpp" line="91"/>
        <source>BothCmd</source>
        <translation>netsh interface ip add dns &quot;以太网&quot; 172.31.1.1 index=2</translation>
    </message>
    <message>
        <location filename="mainwindow.cpp" line="68"/>
        <source>UAT Net Success Tip</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="mainwindow.cpp" line="74"/>
        <source>WorkCmd</source>
        <translation>netsh interface ip set dnsservers name=&quot;以太网&quot; static 10.20.193.2 primary</translation>
    </message>
    <message>
        <location filename="mainwindow.cpp" line="81"/>
        <source>Work Net Success Tip</source>
        <translatorcomment>配置成功，当前网络环境已恢复为内网访问。</translatorcomment>
        <translation>配置成功，当前网络环境已恢复为内网访问。</translation>
    </message>
    <message>
        <location filename="mainwindow.cpp" line="86"/>
        <source>HostWarning</source>
        <translation>注意！
1.该操作非常不建议重复操作，一旦提示成功，无论是否生效，切勿执行第二次，避免意外的错误。
2.若一定要重试，请先选择“收回能力”。
3.若频繁操作后导致异常，请记录下自己的网络设置后进行网络重置即可完全恢复。
4.后续步骤为耗时操作，懒得换线程了，所以UI会失去响应一段时间，预计耗时30s。
5.若程序突然消失，就是被卡巴斯基干掉了，请关闭卡巴斯基的行为检测，或继续使用旧版小工具。</translation>
    </message>
    <message>
        <location filename="mainwindow.cpp" line="134"/>
        <source>Enjoy!</source>
        <translation type="unfinished"></translation>
    </message>
</context>
</TS>
