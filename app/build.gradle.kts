plugins {
  id ("com.android.application")
}

android {
  namespace = "cdroid.app"
  compileSdk = 34

  ndkVersion = "27.1.12297006"

  defaultConfig {
    applicationId = "cdroid.app"
    minSdk = 24
    targetSdk = 36
    versionCode = 1
    versionName = "1.0"

    vectorDrawables.useSupportLibrary = true

    ndk {
      abiFilters += listOf ("armeabi-v7a", "arm64-v8a")
    }
  }

  externalNativeBuild {
    cmake {
      path = file ("../example/CMakeLists.txt")
    }
  }

  compileOptions {
    sourceCompatibility = JavaVersion.VERSION_11
    targetCompatibility = JavaVersion.VERSION_11
  }

  buildTypes {
    release {
      isMinifyEnabled = true
      proguardFiles (getDefaultProguardFile ("proguard-android-optimize.txt"), "proguard-rules.pro")
    }
  }

  buildFeatures {
    viewBinding = true
  }
}

dependencies {
  implementation ("com.google.android.material:material:1.13.0")
}