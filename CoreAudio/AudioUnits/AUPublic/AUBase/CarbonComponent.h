/*
 File:       CarbonCore/Components.h

 Contains:   Component Manager Interfaces.
 The contents of this header file are deprecated.
 Use Foundation or CoreFoundation bundles and plugins instead.

 Copyright:  © 1991-2011 by Apple Inc. All rights reserved.
 */
#ifndef __COMPONENTS__
#define __COMPONENTS__

#ifndef __MACERRORS__
#include <MacErrors.h>
#endif

#ifndef __MACTYPES__
#include <MacTypes.h>
#endif

#include <Availability.h>
#include <MobileCoreServices/MobileCoreServices.h>

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack(push, 2)

    enum {
        kAppleManufacturer            = 'appl', /* Apple supplied components */
        kComponentResourceType        = 'thng', /* a components resource type */
        kComponentAliasResourceType   = 'thga' /* component alias resource type */
    };

    enum {
        kAnyComponentType             = 0,
        kAnyComponentSubType          = 0,
        kAnyComponentManufacturer     = 0,
        kAnyComponentFlagsMask        = 0
    };

    enum {
        cmpThreadSafe                 = 1UL << 28, /* component is thread-safe */
        cmpIsMissing                  = 1UL << 29,
        cmpWantsRegisterMessage       = 1UL << 31
    };

    enum {
        kComponentOpenSelect          = -1,   /* ComponentInstance for this open */
        kComponentCloseSelect         = -2,   /* ComponentInstance for this close */
        kComponentCanDoSelect         = -3,   /* selector # being queried */
        kComponentVersionSelect       = -4,   /* no params */
        kComponentRegisterSelect      = -5,   /* no params */
        kComponentTargetSelect        = -6,   /* ComponentInstance for top of call chain */
        kComponentUnregisterSelect    = -7,   /* no params */
        kComponentGetMPWorkFunctionSelect = -8, /* some params */
        kComponentExecuteWiredActionSelect = -9, /* QTAtomContainer actionContainer, QTAtom actionAtom, QTCustomActionTargetPtr target, QTEventRecordPtr event */
        kComponentGetPublicResourceSelect = -10 /* OSType resourceType, short resourceId, Handle *resource */
    };

    /* Component Resource Extension flags */
    enum {
        componentDoAutoVersion        = (1 << 0),
        componentWantsUnregister      = (1 << 1),
        componentAutoVersionIncludeFlags = (1 << 2),
        componentHasMultiplePlatforms = (1 << 3),
        componentLoadResident         = (1 << 4)
    };



    /* Set Default Component flags */
    enum {
        defaultComponentIdentical     = 0,
        defaultComponentAnyFlags      = 1,
        defaultComponentAnyManufacturer = 2,
        defaultComponentAnySubType    = 4,
        defaultComponentAnyFlagsAnyManufacturer = (defaultComponentAnyFlags + defaultComponentAnyManufacturer),
        defaultComponentAnyFlagsAnyManufacturerAnySubType = (defaultComponentAnyFlags + defaultComponentAnyManufacturer + defaultComponentAnySubType)
    };

    /* RegisterComponentResource flags */
    enum {
        registerComponentGlobal       = 1,
        registerComponentNoDuplicates = 2,
        registerComponentAfterExisting = 4,
        registerComponentAliasesOnly  = 8
    };


    struct ComponentDescription {
        OSType              componentType;          /* A unique 4-byte code indentifying the command set */
        OSType              componentSubType;       /* Particular flavor of this instance */
        OSType              componentManufacturer;  /* Vendor indentification */
        UInt32              componentFlags;         /* 8 each for Component,Type,SubType,Manuf/revision */
        UInt32              componentFlagsMask;     /* Mask for specifying which flags to consider in search, zero during registration */
    };
    typedef struct ComponentDescription     ComponentDescription;

    struct ResourceSpec {
        OSType              resType;                /* 4-byte code    */
        SInt16              resID;                  /*         */
    };
    typedef struct ResourceSpec             ResourceSpec;
    struct ComponentResource {
        ComponentDescription  cd;                   /* Registration parameters */
        ResourceSpec        component;              /* resource where Component code is found */
        ResourceSpec        componentName;          /* name string resource */
        ResourceSpec        componentInfo;          /* info string resource */
        ResourceSpec        componentIcon;          /* icon resource */
    };
    typedef struct ComponentResource        ComponentResource;
    typedef ComponentResource *             ComponentResourcePtr;
    typedef ComponentResourcePtr *          ComponentResourceHandle;
    struct ComponentPlatformInfo {
        SInt32              componentFlags;         /* flags of Component */
        ResourceSpec        component;              /* resource where Component code is found */
        SInt16              platformType;           /* gestaltSysArchitecture result */
    };
    typedef struct ComponentPlatformInfo    ComponentPlatformInfo;
    struct ComponentResourceExtension {
        SInt32              componentVersion;       /* version of Component */
        SInt32              componentRegisterFlags; /* flags for registration */
        SInt16              componentIconFamily;    /* resource id of Icon Family */
    };
    typedef struct ComponentResourceExtension ComponentResourceExtension;
    struct ComponentPlatformInfoArray {
        SInt32              count;
        ComponentPlatformInfo  platformArray[1];
    };
    typedef struct ComponentPlatformInfoArray ComponentPlatformInfoArray;
    struct ExtComponentResource {
        ComponentDescription  cd;                   /* registration parameters */
        ResourceSpec        component;              /* resource where Component code is found */
        ResourceSpec        componentName;          /* name string resource */
        ResourceSpec        componentInfo;          /* info string resource */
        ResourceSpec        componentIcon;          /* icon resource */
        SInt32              componentVersion;       /* version of Component */
        SInt32              componentRegisterFlags; /* flags for registration */
        SInt16              componentIconFamily;    /* resource id of Icon Family */
        SInt32              count;                  /* elements in platformArray */
        ComponentPlatformInfo  platformArray[1];
    };
    typedef struct ExtComponentResource     ExtComponentResource;
    typedef ExtComponentResource *          ExtComponentResourcePtr;
    typedef ExtComponentResourcePtr *       ExtComponentResourceHandle;
    struct ComponentAliasResource {
        ComponentResource   cr;                     /* Registration parameters */
        ComponentDescription  aliasCD;              /* component alias description */
    };
    typedef struct ComponentAliasResource   ComponentAliasResource;
    /*  Structure received by Component:        */
    struct ComponentParameters {
        UInt8               flags;                  /* call modifiers: sync/async, deferred, immed, etc */
        UInt8               paramSize;              /* size in bytes of actual parameters passed to this call */
        SInt16              what;                   /* routine selector, negative for Component management calls */
#if __LP64__

        UInt32              padding;
#endif

        long                params[1];              /* actual parameters for the indicated routine */
    };
    typedef struct ComponentParameters      ComponentParameters;
    struct ComponentRecord {
        long                data[1];
    };
    typedef struct ComponentRecord          ComponentRecord;
    typedef ComponentRecord *               Component;
    struct ComponentInstanceRecord {
        long                data[1];
    };
    typedef struct ComponentInstanceRecord  ComponentInstanceRecord;
    typedef ComponentInstanceRecord *       ComponentInstance;
    struct RegisteredComponentRecord {
        long                data[1];
    };
    typedef struct RegisteredComponentRecord RegisteredComponentRecord;
    typedef RegisteredComponentRecord *     RegisteredComponentRecordPtr;
    struct RegisteredComponentInstanceRecord {
        long                data[1];
    };
    typedef struct RegisteredComponentInstanceRecord RegisteredComponentInstanceRecord;
    typedef RegisteredComponentInstanceRecord * RegisteredComponentInstanceRecordPtr;
    typedef SInt32                          ComponentResult;
    enum {
        platform68k                   = 1,    /* platform type (response from gestaltComponentPlatform) */
        platformPowerPC               = 2,    /* (when gestaltComponentPlatform is not implemented, use */
        platformInterpreted           = 3,    /* gestaltSysArchitecture) */
        platformWin32                 = 4,
        platformPowerPCNativeEntryPoint = 5,
        platformIA32NativeEntryPoint  = 6,
        platformPowerPC64NativeEntryPoint = 7,
        platformX86_64NativeEntryPoint = 8
    };

    enum {
        platformIRIXmips              = 1000,
        platformSunOSsparc            = 1100,
        platformSunOSintel            = 1101,
        platformLinuxppc              = 1200,
        platformLinuxintel            = 1201,
        platformAIXppc                = 1300,
        platformNeXTIntel             = 1400,
        platformNeXTppc               = 1401,
        platformNeXTsparc             = 1402,
        platformNeXT68k               = 1403,
        platformMacOSx86              = 1500
    };

    enum {
        mpWorkFlagDoWork              = (1 << 0),
        mpWorkFlagDoCompletion        = (1 << 1),
        mpWorkFlagCopyWorkBlock       = (1 << 2),
        mpWorkFlagDontBlock           = (1 << 3),
        mpWorkFlagGetProcessorCount   = (1 << 4),
        mpWorkFlagGetIsRunning        = (1 << 6)
    };

    enum {
        cmpAliasNoFlags               = 0,
        cmpAliasOnlyThisFile          = 1
    };

    typedef UInt32                          CSComponentsThreadMode;
    enum {
        kCSAcceptAllComponentsMode    = 0,
        kCSAcceptThreadSafeComponentsOnlyMode = 1
    };
    /*
     The parameter list for each ComponentFunction is unique. It is
     therefore up to users to create the appropriate procInfo for their
     own ComponentFunctions where necessary.
     */
    typedef UniversalProcPtr                ComponentFunctionUPP;



#if TARGET_RT_MAC_CFM
    /*
     CallComponentUPP is a global variable exported from InterfaceLib.
     It is the ProcPtr passed to CallUniversalProc to manually call a component function.
     */
    /*
     *  CallComponentUPP
     *
     *  Availability:
     *    Mac OS X:         not available
     *    CarbonLib:        not available
     *    Non-Carbon CFM:   in InterfaceLib 7.1 and later
     */
    extern UniversalProcPtr CallComponentUPP;
#endif

#define ComponentCallNow( callNumber, paramSize ) \
FIVEWORDINLINE( 0x2F3C,paramSize,callNumber,0x7000,0xA82A )
    
    /* ProcInfos */
    
    /* MixedMode ProcInfo constants for component calls */
    enum {
        uppComponentFunctionImplementedProcInfo    = 0x000002F0,
        uppGetComponentVersionProcInfo             = 0x000000F0,
        uppComponentSetTargetProcInfo              = 0x000003F0,
        uppCallComponentOpenProcInfo               = 0x000003F0,
        uppCallComponentCloseProcInfo              = 0x000003F0,
        uppCallComponentCanDoProcInfo              = 0x000002F0,
        uppCallComponentVersionProcInfo            = 0x000000F0,
        uppCallComponentRegisterProcInfo           = 0x000000F0,
        uppCallComponentTargetProcInfo             = 0x000003F0,
        uppCallComponentUnregisterProcInfo         = 0x000000F0,
        uppCallComponentGetMPWorkFunctionProcInfo  = 0x00000FF0,
        uppCallComponentGetPublicResourceProcInfo  = 0x00003BF0
    };
    
#pragma pack(pop)
    
#ifdef __cplusplus
}
#endif

#endif /* __COMPONENTS__ */

