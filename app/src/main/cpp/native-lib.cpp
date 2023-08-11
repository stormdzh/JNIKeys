#include <jni.h>
#include <string>
#include <stdio.h>

#ifdef _cplusplus
extern "C" {
#endif


const char *AUTH_KEY_DEBUG = "0CC175B9C0F1B6A831C399E269772661";
const char *RELEASE_SIGN_DEBUG = "308202e4308201cc020101300d06092a864886f70d01010b050030373116301406035504030c0d416e64726f69642044656275673110300e060355040a0c07416e64726f6964310b30090603550406130255533020170d3233303632353033343934345a180f32303533303631373033343934345a30373116301406035504030c0d416e64726f69642044656275673110300e060355040a0c07416e64726f6964310b300906035504061302555330820122300d06092a864886f70d01010105000382010f003082010a02820101008badfd693be578d979ca9c7ea5b99549bc437265823e551876e22c6aa63dbcb7e60e8f73315837d8dc7d2ee37bcf920eaf9f98a837ed352039eef1aa5f4bfae5ca5b278e706000d1a1c250e7263e4fdeaf9f06945b195ead35cc3956736549fc9848ce81b5c677ed95b44814dbb0c17cdbb1be36711522e2ebed1f528d6a40ac95444a760bbc34b325166f24378d180e688910e7e3868901383f45de0ef1c330fcb01613feed17153d7ad427be1ae08f421e7b5e24cecdb1e33627d8d1b4d4f2b363ffeb4f8326322883ae8ffb84ab5037fb704cad9ba174e544a0622881ed40535be0a402decb3b48994e8ef18514d44270f60dd330c783d033a624193433b70203010001300d06092a864886f70d01010b0500038201010052434ab446f2f58fedf3da47922fb3c9f0e5009ac1d20a16a145967898497359ac5a6a96529c5156ec97e8af416c09772d7ee97956202bfed57afa252d5b4cbf4f53a33c4089b6b04b935f8ca43551e6e18679437f3c06e98cc24da09f597d1a411fbb89fe076c6afc07d00058f49bb1d4482223538c0fe43dceb82b231da43d5500736356a368055bbf132113965ef3d43ddbe28a106aaee3a347f5d4dc97854ae27d87702d033082101c3e9a1fb2df6501e72ae5ad059b0f43e22a631a45eaa4eaa2514c482da343c41fa6653f8ba35fba0ffb516449fc4f24b8ddb32f7740f226c6a74b985ab8f209ab3a5b6451265c3eac22c91cf25119af1f26129d086d";
const char *AUTH_KEY_RELEASE = "0CC175B9C0F1B6A831C399E269772662";
const char *RELEASE_SIGN_RELEASE = "308202e4308201cc020101300d06092a864886f70d01010b050030373116301406035504030c0d416e64726f69642044656275673110300e060355040a0c07416e64726f6964310b30090603550406130255533020170d3233303632353033343934345a180f32303533303631373033343934345a30373116301406035504030c0d416e64726f69642044656275673110300e060355040a0c07416e64726f6964310b300906035504061302555330820122300d06092a864886f70d01010105000382010f003082010a02820101008badfd693be578d979ca9c7ea5b99549bc437265823e551876e22c6aa63dbcb7e60e8f73315837d8dc7d2ee37bcf920eaf9f98a837ed352039eef1aa5f4bfae5ca5b278e706000d1a1c250e7263e4fdeaf9f06945b195ead35cc3956736549fc9848ce81b5c677ed95b44814dbb0c17cdbb1be36711522e2ebed1f528d6a40ac95444a760bbc34b325166f24378d180e688910e7e3868901383f45de0ef1c330fcb01613feed17153d7ad427be1ae08f421e7b5e24cecdb1e33627d8d1b4d4f2b363ffeb4f8326322883ae8ffb84ab5037fb704cad9ba174e544a0622881ed40535be0a402decb3b48994e8ef18514d44270f60dd330c783d033a624193433b70203010001300d06092a864886f70d01010b0500038201010052434ab446f2f58fedf3da47922fb3c9f0e5009ac1d20a16a145967898497359ac5a6a96529c5156ec97e8af416c09772d7ee97956202bfed57afa252d5b4cbf4f53a33c4089b6b04b935f8ca43551e6e18679437f3c06e98cc24da09f597d1a411fbb89fe076c6afc07d00058f49bb1d4482223538c0fe43dceb82b231da43d5500736356a368055bbf132113965ef3d43ddbe28a106aaee3a347f5d4dc97854ae27d87702d033082101c3e9a1fb2df6501e72ae5ad059b0f43e22a631a45eaa4eaa2514c482da343c41fa6653f8ba35fba0ffb516449fc4f24b8ddb32f7740f226c6a74b985ab8f209ab3a5b6451265c3eac22c91cf25119af1f26129d086d";


static jclass contextClass;
static jclass signatureClass;
static jclass packageNameClass;
static jclass packageInfoClass;


JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {

    JNIEnv *env = NULL;
    jint result = -1;
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_4) != JNI_OK)
        return result;

    contextClass = (jclass) env->NewGlobalRef((env)->FindClass("android/content/Context"));
    signatureClass = (jclass) env->NewGlobalRef((env)->FindClass("android/content/pm/Signature"));
    packageNameClass = (jclass) env->NewGlobalRef(
            (env)->FindClass("android/content/pm/PackageManager"));
    packageInfoClass = (jclass) env->NewGlobalRef(
            (env)->FindClass("android/content/pm/PackageInfo"));

    return JNI_VERSION_1_4;
}

#ifdef _cplusplus
}
#endif
extern "C"
JNIEXPORT jstring JNICALL
Java_com_pinery_jni_KeyStore_getSignKey(JNIEnv *env, jobject thiz, jobject contextObject,
                                        jboolean debug) {
    jmethodID getPackageManagerId = (env)->GetMethodID(contextClass, "getPackageManager",
                                                       "()Landroid/content/pm/PackageManager;");
    jmethodID getPackageNameId = (env)->GetMethodID(contextClass, "getPackageName",
                                                    "()Ljava/lang/String;");
    jmethodID signToStringId = (env)->GetMethodID(signatureClass, "toCharsString",
                                                  "()Ljava/lang/String;");
    jmethodID getPackageInfoId = (env)->GetMethodID(packageNameClass, "getPackageInfo",
                                                    "(Ljava/lang/String;I)Landroid/content/pm/PackageInfo;");
    jobject packageManagerObject = (env)->CallObjectMethod(contextObject, getPackageManagerId);
    jstring packNameString = (jstring) (env)->CallObjectMethod(contextObject, getPackageNameId);
    jobject packageInfoObject = (env)->CallObjectMethod(packageManagerObject, getPackageInfoId,
                                                        packNameString, 64);
    jfieldID signaturefieldID = (env)->GetFieldID(packageInfoClass, "signatures",
                                                  "[Landroid/content/pm/Signature;");
    jobjectArray signatureArray = (jobjectArray) (env)->GetObjectField(packageInfoObject,
                                                                       signaturefieldID);
    jobject signatureObject = (env)->GetObjectArrayElement(signatureArray, 0);

    const char *signStrng = (env)->GetStringUTFChars(
            (jstring) (env)->CallObjectMethod(signatureObject, signToStringId), 0);
    if (debug) {

        if (strcmp(signStrng, RELEASE_SIGN_DEBUG) == 0) {
            return (env)->NewStringUTF(AUTH_KEY_DEBUG);
        } else {
            return (env)->NewStringUTF("");
        }
    } else {
        if (strcmp(signStrng, RELEASE_SIGN_RELEASE) == 0) {
            return (env)->NewStringUTF(AUTH_KEY_RELEASE);
        } else {
            return (env)->NewStringUTF("");
        }
    }
}
