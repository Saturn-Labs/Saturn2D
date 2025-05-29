#pragma once
#include <tuple>

namespace Saturn {
    template<typename RetType, typename... Params>
    struct FuncType { };

    template<typename BindRetType, typename... BindParams, typename UnbindRetType, typename... UnbindParams>
    class IBindableResource<BindRetType(BindParams...), UnbindRetType(UnbindParams...)> {
        virtual ~IBindableResource() = default;
        virtual BindRetType bind(BindParams...) = 0;
        virtual UnbindRetType unbind(UnbindParams...) = 0;
        virtual GraphicsResourceId getCurrentBound() = 0;
    };
}
