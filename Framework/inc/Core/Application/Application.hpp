#pragma once
#include "Core/Common/Types.hpp"

namespace Saturn {
    class Application {
    private:
        static bool _hasOneApplication;

    protected:
        String _name = "SaturnFX";
        String _author = "Saturn Labs";

        Application(const String& name, const String& author);

    public:
        virtual ~Application();
        virtual void start();
        virtual void stop();

    };

    extern Unique<Application> CreateApplication(i32 argc, CString argv[]);
}
