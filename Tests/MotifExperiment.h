#pragma once
#include <type_traits>
#include <utility>
// Historical feature experiments isolate their own change with an explicit
// composition policy. The production defaults are tested by MotifReprise,
// MotifWindowRegression, the actual processor and the 126-case musical audit.
// SFINAE lets the same offline probe compile against its pinned historical headers;
// this helper is never included by the plugin or the composition engine.
template<class Settings,class=void>struct HasMotifEstablishment:std::false_type{};
template<class Settings>struct HasMotifEstablishment<Settings,std::void_t<
    decltype(std::declval<Settings>().policy.motif.establishOriginal),
    decltype(std::declval<Settings>().policy.popHooks.recurrence.preserveContour)>>:std::true_type{};
template<class Settings>inline void pinMotifExperiment(Settings& s)
{
    if constexpr(HasMotifEstablishment<Settings>::value)
    {
        s.policy.motif.establishOriginal=false;s.policy.motif.preserveContour=false;
        s.policy.popHooks.recurrence.establishOriginal=false;s.policy.popHooks.recurrence.preserveContour=false;
    }
}
