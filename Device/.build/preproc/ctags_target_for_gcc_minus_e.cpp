# 1 "c:\\Users\\zzh\\Documents\\temp\\devkit\\zzhdevkit\\Device\\main.ino"
# 1 "c:\\Users\\zzh\\Documents\\temp\\devkit\\zzhdevkit\\Device\\main.ino"
//
// Core header files for C and IoTHub layer
//
# 5 "c:\\Users\\zzh\\Documents\\temp\\devkit\\zzhdevkit\\Device\\main.ino" 2
# 6 "c:\\Users\\zzh\\Documents\\temp\\devkit\\zzhdevkit\\Device\\main.ino" 2
# 7 "c:\\Users\\zzh\\Documents\\temp\\devkit\\zzhdevkit\\Device\\main.ino" 2
# 8 "c:\\Users\\zzh\\Documents\\temp\\devkit\\zzhdevkit\\Device\\main.ino" 2
# 9 "c:\\Users\\zzh\\Documents\\temp\\devkit\\zzhdevkit\\Device\\main.ino" 2
# 10 "c:\\Users\\zzh\\Documents\\temp\\devkit\\zzhdevkit\\Device\\main.ino" 2
# 11 "c:\\Users\\zzh\\Documents\\temp\\devkit\\zzhdevkit\\Device\\main.ino" 2

// IoT Central requires DPS.  Include required header and constants
# 14 "c:\\Users\\zzh\\Documents\\temp\\devkit\\zzhdevkit\\Device\\main.ino" 2
# 15 "c:\\Users\\zzh\\Documents\\temp\\devkit\\zzhdevkit\\Device\\main.ino" 2
# 16 "c:\\Users\\zzh\\Documents\\temp\\devkit\\zzhdevkit\\Device\\main.ino" 2
# 17 "c:\\Users\\zzh\\Documents\\temp\\devkit\\zzhdevkit\\Device\\main.ino" 2

static bool iotHubConnected = false;

// State of DPS registration process.  We cannot proceed with DPS until we get into the state APP_DPS_REGISTRATION_SUCCEEDED.
typedef enum APP_DPS_REGISTRATION_STATUS_TAG
{
    APP_DPS_REGISTRATION_PENDING,
    APP_DPS_REGISTRATION_SUCCEEDED,
    APP_DPS_REGISTRATION_FAILED
} APP_DPS_REGISTRATION_STATUS;

const SECURE_DEVICE_TYPE secureDeviceTypeForProvisioning = SECURE_DEVICE_TYPE_SYMMETRIC_KEY;
const IOTHUB_SECURITY_TYPE secureDeviceTypeForIotHub = IOTHUB_SECURITY_TYPE_SYMMETRIC_KEY;

// The DPS global device endpoint
static const char *globalDpsEndpoint = "global.azure-devices-provisioning.net";

// TODO: Specify DPS scope ID if you intend on using DPS / IoT Central.
static const char *dpsIdScope = "0ne000690B2";

// TODO: Specify symmetric keys if you intend on using DPS / IoT Central and symmetric key based auth.
static const char *sasKey = "pFRBFgtTirJSjj/+E6xMiDtM1rNHNeV1BU6tX0eD56E=";

// TODO: specify your device ID
static const char *registrationId = "zzhsense";

// TODO: Fill in DIGITALTWIN_DEVICE_CAPABILITY_MODEL_ID and DIGITALTWIN_DEVICE_CAPABILITY_MODEL_INLINE_DATA if you indend on using IoT Central.



static const char *digitalTwinSample_CustomProvisioningData = "{"
                                                              "\"__iot:interfaces\":"
                                                              "{"
                                                              "\"CapabilityModelId\": \"" "urn:bugbash0725:sample_device:1" "\" ,"
                                                              "\"CapabilityModel\": \"" "{}" "\""
                                                              "}"
                                                              "}";

// Amount in ms to sleep between querying state from DPS registration loop
static const int dpsRegistrationPollSleep = 100;

// Maximum amount of times we'll poll for DPS registration being ready, 1 min.
static const int dpsRegistrationMaxPolls = (60 * 1000 / dpsRegistrationPollSleep);

// State of DigitalTwin registration process.  We cannot proceed with DigitalTwin until we get into the state APP_DIGITALTWIN_REGISTRATION_SUCCEEDED.
typedef enum APP_DIGITALTWIN_REGISTRATION_STATUS_TAG
{
    APP_DIGITALTWIN_REGISTRATION_PENDING,
    APP_DIGITALTWIN_REGISTRATION_SUCCEEDED,
    APP_DIGITALTWIN_REGISTRATION_FAILED
} APP_DIGITALTWIN_REGISTRATION_STATUS;



static char *dpsIotHubUri;
static char *dpsDeviceId;

static void provisioningRegisterCallback(PROV_DEVICE_RESULT register_result, const char *iothub_uri, const char *device_id, void *user_context)
{
    APP_DPS_REGISTRATION_STATUS *appDpsRegistrationStatus = (APP_DPS_REGISTRATION_STATUS *)user_context;

    if (register_result != PROV_DEVICE_RESULT_OK)
    {
        do{ { if (0) { (void)printf("DPS Provisioning callback called with error state %d", register_result); } { LOGGER_LOG l = xlogging_get_log_function(); if (l != 
# 80 "c:\\Users\\zzh\\Documents\\temp\\devkit\\zzhdevkit\\Device\\main.ino" 3 4
       __null
# 80 "c:\\Users\\zzh\\Documents\\temp\\devkit\\zzhdevkit\\Device\\main.ino"
       ) l(AZ_LOG_ERROR, "c:\\Users\\zzh\\Documents\\temp\\devkit\\zzhdevkit\\Device\\main.ino", __func__, 80, 0x01, "DPS Provisioning callback called with error state %d", register_result); } }; }while((void)0,0);
        *appDpsRegistrationStatus = APP_DPS_REGISTRATION_FAILED;
    }
    else
    {
        if ((mallocAndStrcpy_s(&dpsIotHubUri, iothub_uri) != 0) ||
            (mallocAndStrcpy_s(&dpsDeviceId, device_id) != 0))
        {
            do{ { if (0) { (void)printf("Unable to copy provisioning information"); } { LOGGER_LOG l = xlogging_get_log_function(); if (l != 
# 88 "c:\\Users\\zzh\\Documents\\temp\\devkit\\zzhdevkit\\Device\\main.ino" 3 4
           __null
# 88 "c:\\Users\\zzh\\Documents\\temp\\devkit\\zzhdevkit\\Device\\main.ino"
           ) l(AZ_LOG_ERROR, "c:\\Users\\zzh\\Documents\\temp\\devkit\\zzhdevkit\\Device\\main.ino", __func__, 88, 0x01, "Unable to copy provisioning information"); } }; }while((void)0,0);
            *appDpsRegistrationStatus = APP_DPS_REGISTRATION_FAILED;
        }
        else
        {
            do{{ if (0) { (void)printf("Provisioning callback indicates success.  iothubUri=%s, deviceId=%s", dpsIotHubUri, dpsDeviceId); } { LOGGER_LOG l = xlogging_get_log_function(); if (l != 
# 93 "c:\\Users\\zzh\\Documents\\temp\\devkit\\zzhdevkit\\Device\\main.ino" 3 4
           __null
# 93 "c:\\Users\\zzh\\Documents\\temp\\devkit\\zzhdevkit\\Device\\main.ino"
           ) l(AZ_LOG_INFO, "c:\\Users\\zzh\\Documents\\temp\\devkit\\zzhdevkit\\Device\\main.ino", __func__, 93, 0x01, "Provisioning callback indicates success.  iothubUri=%s, deviceId=%s", dpsIotHubUri, dpsDeviceId); } }; }while((void)0,0);
            *appDpsRegistrationStatus = APP_DPS_REGISTRATION_SUCCEEDED;
        }
    }
}

static bool registerDevice(bool traceOn)
{
    PROV_DEVICE_RESULT provDeviceResult;
    PROV_DEVICE_LL_HANDLE provDeviceLLHandle = 
# 102 "c:\\Users\\zzh\\Documents\\temp\\devkit\\zzhdevkit\\Device\\main.ino" 3 4
                                              __null
# 102 "c:\\Users\\zzh\\Documents\\temp\\devkit\\zzhdevkit\\Device\\main.ino"
                                                  ;
    bool result = false;

    APP_DPS_REGISTRATION_STATUS appDpsRegistrationStatus = APP_DPS_REGISTRATION_PENDING;

    if (IoTHub_Init() != 0)
    {
        do{ { if (0) { (void)printf("IoTHub_Init failed"); } { LOGGER_LOG l = xlogging_get_log_function(); if (l != 
# 109 "c:\\Users\\zzh\\Documents\\temp\\devkit\\zzhdevkit\\Device\\main.ino" 3 4
       __null
# 109 "c:\\Users\\zzh\\Documents\\temp\\devkit\\zzhdevkit\\Device\\main.ino"
       ) l(AZ_LOG_ERROR, "c:\\Users\\zzh\\Documents\\temp\\devkit\\zzhdevkit\\Device\\main.ino", __func__, 109, 0x01, "IoTHub_Init failed"); } }; }while((void)0,0);
        return false;
    }

    if (prov_dev_set_symmetric_key_info(registrationId, sasKey) != 0)
    {
        do{ { if (0) { (void)printf("prov_dev_set_symmetric_key_info failed."); } { LOGGER_LOG l = xlogging_get_log_function(); if (l != 
# 115 "c:\\Users\\zzh\\Documents\\temp\\devkit\\zzhdevkit\\Device\\main.ino" 3 4
       __null
# 115 "c:\\Users\\zzh\\Documents\\temp\\devkit\\zzhdevkit\\Device\\main.ino"
       ) l(AZ_LOG_ERROR, "c:\\Users\\zzh\\Documents\\temp\\devkit\\zzhdevkit\\Device\\main.ino", __func__, 115, 0x01, "prov_dev_set_symmetric_key_info failed."); } }; }while((void)0,0);
    }
    else if (prov_dev_security_init(secureDeviceTypeForProvisioning) != 0)
    {
        do{ { if (0) { (void)printf("prov_dev_security_init failed"); } { LOGGER_LOG l = xlogging_get_log_function(); if (l != 
# 119 "c:\\Users\\zzh\\Documents\\temp\\devkit\\zzhdevkit\\Device\\main.ino" 3 4
       __null
# 119 "c:\\Users\\zzh\\Documents\\temp\\devkit\\zzhdevkit\\Device\\main.ino"
       ) l(AZ_LOG_ERROR, "c:\\Users\\zzh\\Documents\\temp\\devkit\\zzhdevkit\\Device\\main.ino", __func__, 119, 0x01, "prov_dev_security_init failed"); } }; }while((void)0,0);
    }
    else if ((provDeviceLLHandle = Prov_Device_LL_Create(globalDpsEndpoint, dpsIdScope, Prov_Device_MQTT_Protocol)) == 
# 121 "c:\\Users\\zzh\\Documents\\temp\\devkit\\zzhdevkit\\Device\\main.ino" 3 4
                                                                                                                      __null
# 121 "c:\\Users\\zzh\\Documents\\temp\\devkit\\zzhdevkit\\Device\\main.ino"
                                                                                                                          )
    {
        do{ { if (0) { (void)printf("failed calling Prov_Device_Create"); } { LOGGER_LOG l = xlogging_get_log_function(); if (l != 
# 123 "c:\\Users\\zzh\\Documents\\temp\\devkit\\zzhdevkit\\Device\\main.ino" 3 4
       __null
# 123 "c:\\Users\\zzh\\Documents\\temp\\devkit\\zzhdevkit\\Device\\main.ino"
       ) l(AZ_LOG_ERROR, "c:\\Users\\zzh\\Documents\\temp\\devkit\\zzhdevkit\\Device\\main.ino", __func__, 123, 0x01, "failed calling Prov_Device_Create"); } }; }while((void)0,0);
    }
    else if ((provDeviceResult = Prov_Device_LL_SetOption(provDeviceLLHandle, PROV_OPTION_LOG_TRACE, &traceOn)) != PROV_DEVICE_RESULT_OK)
    {
        do{ { if (0) { (void)printf("Setting provisioning tracing on failed, error=%d", provDeviceResult); } { LOGGER_LOG l = xlogging_get_log_function(); if (l != 
# 127 "c:\\Users\\zzh\\Documents\\temp\\devkit\\zzhdevkit\\Device\\main.ino" 3 4
       __null
# 127 "c:\\Users\\zzh\\Documents\\temp\\devkit\\zzhdevkit\\Device\\main.ino"
       ) l(AZ_LOG_ERROR, "c:\\Users\\zzh\\Documents\\temp\\devkit\\zzhdevkit\\Device\\main.ino", __func__, 127, 0x01, "Setting provisioning tracing on failed, error=%d", provDeviceResult); } }; }while((void)0,0);
    }
    else if ((provDeviceResult = Prov_Device_LL_SetOption(provDeviceLLHandle, "TrustedCerts", certificates)) != PROV_DEVICE_RESULT_OK)
    {
        do{ { if (0) { (void)printf("Setting provisioning TrustedCerts failed, error=%d", provDeviceResult); } { LOGGER_LOG l = xlogging_get_log_function(); if (l != 
# 131 "c:\\Users\\zzh\\Documents\\temp\\devkit\\zzhdevkit\\Device\\main.ino" 3 4
       __null
# 131 "c:\\Users\\zzh\\Documents\\temp\\devkit\\zzhdevkit\\Device\\main.ino"
       ) l(AZ_LOG_ERROR, "c:\\Users\\zzh\\Documents\\temp\\devkit\\zzhdevkit\\Device\\main.ino", __func__, 131, 0x01, "Setting provisioning TrustedCerts failed, error=%d", provDeviceResult); } }; }while((void)0,0);
    }
    else if ((provDeviceResult = Prov_Device_LL_Set_Provisioning_Payload(provDeviceLLHandle, digitalTwinSample_CustomProvisioningData)) != PROV_DEVICE_RESULT_OK)
    {
        do{ { if (0) { (void)printf("Failed setting provisioning data, error=%d", provDeviceResult); } { LOGGER_LOG l = xlogging_get_log_function(); if (l != 
# 135 "c:\\Users\\zzh\\Documents\\temp\\devkit\\zzhdevkit\\Device\\main.ino" 3 4
       __null
# 135 "c:\\Users\\zzh\\Documents\\temp\\devkit\\zzhdevkit\\Device\\main.ino"
       ) l(AZ_LOG_ERROR, "c:\\Users\\zzh\\Documents\\temp\\devkit\\zzhdevkit\\Device\\main.ino", __func__, 135, 0x01, "Failed setting provisioning data, error=%d", provDeviceResult); } }; }while((void)0,0);
    }
    else if ((provDeviceResult = Prov_Device_LL_Register_Device(provDeviceLLHandle, provisioningRegisterCallback, &appDpsRegistrationStatus, 
# 137 "c:\\Users\\zzh\\Documents\\temp\\devkit\\zzhdevkit\\Device\\main.ino" 3 4
                                                                                                                                            __null
# 137 "c:\\Users\\zzh\\Documents\\temp\\devkit\\zzhdevkit\\Device\\main.ino"
                                                                                                                                                , 
# 137 "c:\\Users\\zzh\\Documents\\temp\\devkit\\zzhdevkit\\Device\\main.ino" 3 4
                                                                                                                                                  __null
# 137 "c:\\Users\\zzh\\Documents\\temp\\devkit\\zzhdevkit\\Device\\main.ino"
                                                                                                                                                      )) != PROV_DEVICE_RESULT_OK)
    {
        do{ { if (0) { (void)printf("Prov_Device_Register_Device failed, error=%d", provDeviceResult); } { LOGGER_LOG l = xlogging_get_log_function(); if (l != 
# 139 "c:\\Users\\zzh\\Documents\\temp\\devkit\\zzhdevkit\\Device\\main.ino" 3 4
       __null
# 139 "c:\\Users\\zzh\\Documents\\temp\\devkit\\zzhdevkit\\Device\\main.ino"
       ) l(AZ_LOG_ERROR, "c:\\Users\\zzh\\Documents\\temp\\devkit\\zzhdevkit\\Device\\main.ino", __func__, 139, 0x01, "Prov_Device_Register_Device failed, error=%d", provDeviceResult); } }; }while((void)0,0);
    }
    else
    {
        // Pulling the registration status
        for (int i = 0; (i < dpsRegistrationMaxPolls) && (appDpsRegistrationStatus == APP_DPS_REGISTRATION_PENDING); i++)
        {
            ThreadAPI_Sleep(dpsRegistrationPollSleep);
            Prov_Device_LL_DoWork(provDeviceLLHandle);
        }

        if (appDpsRegistrationStatus == APP_DPS_REGISTRATION_SUCCEEDED)
        {
            do{{ if (0) { (void)printf("DPS successfully registered.  Continuing on to creation of IoTHub device client handle."); } { LOGGER_LOG l = xlogging_get_log_function(); if (l != 
# 152 "c:\\Users\\zzh\\Documents\\temp\\devkit\\zzhdevkit\\Device\\main.ino" 3 4
           __null
# 152 "c:\\Users\\zzh\\Documents\\temp\\devkit\\zzhdevkit\\Device\\main.ino"
           ) l(AZ_LOG_INFO, "c:\\Users\\zzh\\Documents\\temp\\devkit\\zzhdevkit\\Device\\main.ino", __func__, 152, 0x01, "DPS successfully registered.  Continuing on to creation of IoTHub device client handle."); } }; }while((void)0,0);
            result = true;
        }
        else if (appDpsRegistrationStatus == APP_DPS_REGISTRATION_PENDING)
        {
            do{ { if (0) { (void)printf("Timed out attempting to register DPS device"); } { LOGGER_LOG l = xlogging_get_log_function(); if (l != 
# 157 "c:\\Users\\zzh\\Documents\\temp\\devkit\\zzhdevkit\\Device\\main.ino" 3 4
           __null
# 157 "c:\\Users\\zzh\\Documents\\temp\\devkit\\zzhdevkit\\Device\\main.ino"
           ) l(AZ_LOG_ERROR, "c:\\Users\\zzh\\Documents\\temp\\devkit\\zzhdevkit\\Device\\main.ino", __func__, 157, 0x01, "Timed out attempting to register DPS device"); } }; }while((void)0,0);
        }
        else
        {
            do{ { if (0) { (void)printf("Error registering device for DPS"); } { LOGGER_LOG l = xlogging_get_log_function(); if (l != 
# 161 "c:\\Users\\zzh\\Documents\\temp\\devkit\\zzhdevkit\\Device\\main.ino" 3 4
           __null
# 161 "c:\\Users\\zzh\\Documents\\temp\\devkit\\zzhdevkit\\Device\\main.ino"
           ) l(AZ_LOG_ERROR, "c:\\Users\\zzh\\Documents\\temp\\devkit\\zzhdevkit\\Device\\main.ino", __func__, 161, 0x01, "Error registering device for DPS"); } }; }while((void)0,0);
        }
    }

    if (provDeviceLLHandle != 
# 165 "c:\\Users\\zzh\\Documents\\temp\\devkit\\zzhdevkit\\Device\\main.ino" 3 4
                             __null
# 165 "c:\\Users\\zzh\\Documents\\temp\\devkit\\zzhdevkit\\Device\\main.ino"
                                 )
    {
        Prov_Device_LL_Destroy(provDeviceLLHandle);
    }
    IoTHub_Deinit();

    return result;
}

void setup()
{
    char buff[512];

    // Initialize the board
    int ret = initIoTDevKit(1);
    if (ret != 0)
    {
        Screen.print(1, "Failed to \r\ninitialize the\r\nIoT DevKit.");
        return;
    }
    else
    {
        IPAddress ip = WiFi.localIP();
        snprintf(buff, sizeof(buff), "%s\r\nWiFi Connected\r\n%s", WiFi.SSID(), ip.get_address());
        Screen.print(1, buff);
    }

    // Initialize device model application
    if (registerDevice(false))
    {
        Screen.print(1, "Connecting\r\n IoT Hub...");

        buff[0] = 0;
        if (secureDeviceTypeForProvisioning == SECURE_DEVICE_TYPE_SYMMETRIC_KEY)
        {
            snprintf(buff, sizeof(buff),
                     "HostName=%s;DeviceId=%s;SharedAccessKey=%s",
                     dpsIotHubUri,
                     dpsDeviceId,
                     sasKey);
        }
        else if (secureDeviceTypeForProvisioning == SECURE_DEVICE_TYPE_X509)
        {
            snprintf(buff, sizeof(buff),
                     "HostName=%s;DeviceId=%s;UseProvisioning=true",
                     dpsIotHubUri,
                     dpsDeviceId);
        }

        if (pnp_device_initialize(buff, certificates) != 0)
        {
            digitalWrite(LED_AZURE, 0);
            Screen.print(1, "Init failed!\r\nCheck log for\r\n more detail.");
            iotHubConnected = false;
        }
        else
        {
            digitalWrite(LED_AZURE, 1);
            Screen.print(1, "PnP Enabled\r\nRunning...");
            iotHubConnected = true;
        }
    }
    else
    {
        digitalWrite(LED_AZURE, 0);
        Screen.print(1, "Init failed!\r\nCheck log for\r\n more detail.");
        iotHubConnected = false;
    }
}

void loop()
{
    // put your main code here, to run repeatedly:
    if (iotHubConnected)
    {
        pnp_device_run();
    }

    invokeDevKitPeripheral();
    delay(500);
}
