#include <jni.h>
#include <string>
#include <stdio.h>

#ifdef _cplusplus
extern "C" {
#endif


const char *AUTH_KEY_DEBUG = "0CC175B9C0F1B6A831C399E269772661";
const char *RELEASE_SIGN_DEBUG = "308201dd30820146020101300d06092a864886f70d010105050030373116301406035504030c0d416e64726f69642044656275673110300e060355040a0c07416e64726f6964310b3009060355040613025553301e170d3139303532373131333934335a170d3439303531393131333934335a30373116301406035504030c0d416e64726f69642044656275673110300e060355040a0c07416e64726f6964310b300906035504061302555330819f300d06092a864886f70d010101050003818d003081890281810097f09a54d93110c31876894fdb72e35c459bd0da9e59449f7e83143da936bd7d573d97d8ca0a7a7a7e68decb06adb5eb33d90bc0478bb3e34c7141e7d70a867928eeaff175b94c6b4a2ba1b99467a9c495a1d087e23417a0436868eed524c59139a76f35f87d9a3c0296b8a8607c77d7543ba13ece62f0fc54b1f9e315111f2f0203010001300d06092a864886f70d0101050500038181008b39f42f99c5f2f71d0c1289c2bc21dd3be3fd8708d498e09bf8092e6bfa425cc6891d1bbbdf6023a2f8dc91c1cb7d521eb54275d9fbdafccb3f3c3ac0e60a41c0c6b4b08b2b9d815783dfc6f2d247d6ca76f87e08d48957c5e8a7810e4870b45a95442a9240e48317597c84957212320a42c5b97c7f08ccc039262b6c1085bc";
const char *AUTH_KEY_RELEASE = "0CC175B9C0F1B6A831C399E269772662";
const char *RELEASE_SIGN_RELEASE = "308201dd30820146020101300d06092a864886f70d010105050030373116301406035504030c0d416e64726f69642044656275673110300e060355040a0c07416e64726f6964310b3009060355040613025553301e170d3139303532373131333934335a170d3439303531393131333934335a30373116301406035504030c0d416e64726f69642044656275673110300e060355040a0c07416e64726f6964310b300906035504061302555330819f300d06092a864886f70d010101050003818d003081890281810097f09a54d93110c31876894fdb72e35c459bd0da9e59449f7e83143da936bd7d573d97d8ca0a7a7a7e68decb06adb5eb33d90bc0478bb3e34c7141e7d70a867928eeaff175b94c6b4a2ba1b99467a9c495a1d087e23417a0436868eed524c59139a76f35f87d9a3c0296b8a8607c77d7543ba13ece62f0fc54b1f9e315111f2f0203010001300d06092a864886f70d0101050500038181008b39f42f99c5f2f71d0c1289c2bc21dd3be3fd8708d498e09bf8092e6bfa425cc6891d1bbbdf6023a2f8dc91c1cb7d521eb54275d9fbdafccb3f3c3ac0e60a41c0c6b4b08b2b9d815783dfc6f2d247d6ca76f87e08d48957c5e8a7810e4870b45a95442a9240e48317597c84957212320a42c5b97c7f08ccc039262b6c1085bc";


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
