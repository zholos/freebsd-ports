--- source/core/shape/truetype.h
+++ source/core/shape/truetype.h
@@ -102,7 +102,7 @@
         virtual void Transform(const TRANSFORM *);
         virtual void Compute_BBox();
 
-        static void ProcessNewTTF(CSG *Object, TrueTypeFont* font, const UCS2 *text_string, DBL depth, const Vector3d& offset, Parser *parser, shared_ptr<SceneData>& sceneData);
+        static void ProcessNewTTF(CSG *Object, TrueTypeFont* font, const UCS2 *text_string, DBL depth, const Vector3d& offset, Parser *parser);
     protected:
         bool Inside_Glyph(double x, double y, const GlyphStruct* glyph) const;
         int solve_quad(double *x, double *y, double mindist, DBL maxdist) const;
--- source/core/shape/truetype.cpp
+++ source/core/shape/truetype.cpp
@@ -469,7 +469,7 @@
 *   (triggered when filename is null) - Oct 2012 [JG]
 *
 ******************************************************************************/
-void TrueType::ProcessNewTTF(CSG *Object, TrueTypeFont *ffile, const UCS2 *text_string, DBL depth, const Vector3d& offset, Parser *parser, shared_ptr<SceneData>& sceneData)
+void TrueType::ProcessNewTTF(CSG *Object, TrueTypeFont *ffile, const UCS2 *text_string, DBL depth, const Vector3d& offset, Parser *parser)
 {
     Vector3d local_offset, total_offset;
     TrueType *ttf;
--- source/parser/parser.cpp
+++ source/parser/parser.cpp
@@ -6222,7 +6222,7 @@
 
     /* Process all this good info */
     Object = new CSGUnion();
-    TrueType::ProcessNewTTF(reinterpret_cast<CSG *>(Object), font, text_string, depth, offset, this, dynamic_pointer_cast<SceneData>(sceneData));
+    TrueType::ProcessNewTTF(reinterpret_cast<CSG *>(Object), font, text_string, depth, offset, this);
     if (filename)
     {
         /* Free up the filename  */
