//
// Created by 29764 on 2025/7/16.
//

#ifndef MYSPHSOLVER_HPP
#define MYSPHSOLVER_HPP


#include <vector>
#include <set>

#include "Framework/Solver.hpp"
#include "MYSPHrtData.hpp"
#include "Modules/NeighborSearch/UGNS/UniformGridNeighborSearch.hpp"

namespace VT_Physics::mysph {

    inline const std::vector<std::string> MYSPHConfigRequiredKeys = {
            "animationTime",
            "timeStep",
            "particleRadius",
            "simSpaceLB",
            "simSpaceSize",
            "maxNeighborNum",
            "fPartRestDensity",
            "bPartRestDensity",
            "fPartRestViscosity",
            "divFreeThreshold",
            "incompThreshold",
            "surfaceTensionCoefficient",
    };

    inline const std::vector<std::string> MYSPHConfigOptionalKeys = {
            "enable",
            "gravity",
    };

    inline const std::vector<std::string> MYSPHSolverObjectComponentConfigRequiredKeys = {
            "solverType",
            "exportFlag",
            "velocityStart",
            "colorStart",
    };

    inline const std::set<uint8_t> MYSPHSolverSupportedMaterials = {
            EPM_FLUID,
            EPM_BOUNDARY
    };

    class MYSPHSolver : public Solver {
    public:
        MYSPHSolver() = delete;

        MYSPHSolver(uint32_t cudaThreadSize);

        virtual ~MYSPHSolver() override = default;

        virtual json getSolverConfigTemplate() const override;

        virtual bool setConfig(json config) override;

        virtual bool setConfigByFile(std::string config_file) override;

        virtual json getSolverObjectComponentConfigTemplate() override;

        virtual bool initialize() override;

        virtual bool run() override;

        virtual bool tickNsteps(uint32_t n) override;

        virtual bool attachObject(Object *obj) override;

        virtual bool attachObjects(std::vector<Object *> objs) override;

        virtual bool reset() override;

        virtual void destroy() override;

    protected:
        virtual bool tick() override;

        virtual bool checkConfig() const override;

    private:
        void exportData();

    private:
        json m_configData;
        Data *m_host_data{nullptr};
        Data *m_device_data{nullptr};
        bool m_isInitialized{false};
        bool m_isCrashed{false};
        uint32_t m_frameCount{0};
        uint32_t m_outputFrameCount{0};
        bool m_doExportFlag{false};
        std::vector<Object *> m_attached_objs;
        UGNS::UniformGirdNeighborSearcher m_neighborSearcher;

        std::vector<float3> m_host_pos;
        std::vector<float3> m_host_vel;
        std::vector<int> m_host_mat;
        std::vector<float3> m_host_color;
    };
}

#endif //MYSPHSOLVER_HPP
