C:\Factory\Tools\RDMD.exe /RC out

SET RAWKEY=e19385c677745379d6cbf5451e9c4136

C:\Factory\SubTools\makeAESCluster.exe Picture.txt     out\Picture.dat     %RAWKEY% 110000000
C:\Factory\SubTools\makeAESCluster.exe Music.txt       out\Music.dat       %RAWKEY% 120000000
C:\Factory\SubTools\makeAESCluster.exe SoundEffect.txt out\SoundEffect.dat %RAWKEY% 130000000
C:\Factory\SubTools\makeAESCluster.exe Etcetera.txt    out\Etcetera.dat    %RAWKEY% 140000000

COPY /B Claris\Release\Claris.exe out\Actor83_1.exe
C:\Factory\Tools\xcp.exe doc out
ren out\Manual.txt ƒ}ƒjƒ…ƒAƒ‹.txt

C:\Factory\SubTools\zip.exe /G out Actor83_1
C:\Factory\Tools\summd5.exe /M out

PAUSE
