--- unix/prebuild.sh
+++ unix/prebuild.sh
@@ -353,8 +353,8 @@
   for file in \
     AUTHORS ChangeLog configure.ac COPYING NEWS README VERSION \
     povray.1 povray.conf \
-    scripts/ \
-    ../distribution/ini/ ../distribution/include/ ../distribution/scenes/
+    scripts \
+    ../distribution/ini ../distribution/include ../distribution/scenes
   do
     out=`basename $file`
     echo "Create ../$out`test -d $file && echo /`"
@@ -724,7 +724,7 @@
 autoheader --warnings=all
 
 # Create all Makefile.in's from Makefile.am's
-automake --warnings=all ###--ignore-deps
+automake --add-missing --warnings=all ###--ignore-deps
 
 # Create configure from configure.ac
 autoconf --warnings=all
