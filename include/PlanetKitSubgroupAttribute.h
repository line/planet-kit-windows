// Copyright 2022 LINE Plus Corporation
//
// LINE Plus Corporation licenses this file to you under the Apache License,
// version 2.0 (the "License"); you may not use this file except in compliance
// with the License. You may obtain a copy of the License at:
//
//   https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
// WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
// License for the specific language governing permissions and limitations
// under the License.

#pragma once

#include "PlanetKit.h"
#include "PlanetKitSubgroupDefine.h"

namespace PlanetKit {
    /**
     * Information class about Subgroup's attribute.
     */
    class PLANETKIT_API SubgroupAttribute {
    public:
        virtual ~SubgroupAttribute() { }

        /// Checks whether video update is enabled for this subgroup.
        virtual bool IsEnableVideoUpdate() = 0;
        /// Checks whether the subgroup's received audio is silenced.
        virtual bool IsSilenced() = 0;
        /// Checks whether the subgroup's received audio auto volume control is enabled.
        virtual bool IsPeersAudioAutoVolumeControlFocused() = 0;
        /// Checks whether DataSession is enabled for this subgroup.
        virtual bool IsUsingDataSession() = 0;
        /// Gets the peer update type.
        virtual ESubgroupPeerUpdateType GetPeerUpdateType() = 0;
    };

    typedef SharedPtr<SubgroupAttribute> SubgroupAttributePtr;
};