#pragma once

#include <limits>
#include "graph.hpp"

namespace GoGraph::Utils
{
    template<int VertexCount, int EdgeCount>
    std::array<float, VertexCount> sssp_async(
        const GraphIterator<VertexCount, EdgeCount>& f_begin,
        const GraphIterator<VertexCount, EdgeCount>& f_end,
        int f_source,
        bool f_isLoggingActive = false,
        float f_epsilon = 1e-6f,
        int f_maxIterations = 1000)
    {
        std::array<float, VertexCount> dist;
        dist.fill(std::numeric_limits<float>::infinity());
        dist[f_source] = 0.f;

        int iteration{ 0 };

        bool changed{ true };
        for (int i = 0; i < f_maxIterations && changed; ++i)
        {
            if (f_isLoggingActive)
            {
                std::cout << "[sssp_async] Currently: iteration #" << i + 1 << "\n";
            }
            
            changed = false;
            for (auto it = f_begin; it != f_end; ++it)
            {                
                for (const auto& [w, u, v] : it->m_inEdges)
                {
                    const auto du = dist[u];
                    const auto dv = dist[v];
                    if (du + w < dv)
                    {
                        if (f_isLoggingActive)
                        {
                            std::cout << "[sssp_async] SP changed for " << v << " from " << dist[v] << " to " << du + w << " based on " << u << "\n";
                        }
                        dist[v] = du + w;
                        changed = true;
                    }
                }
            }

            if (changed)
            {
                iteration++;
            }
        }

        if (f_isLoggingActive)
        {
            std::cout << "[sssp_async] Converged in " << iteration << " iterations.\n";
        }

        return dist;
    }

    template<int VertexCount>
    int p(int u, const std::array<int, VertexCount>& f_processOrder)
    {
        for (auto i = 0; i < VertexCount; i++)
        {
            if (u == f_processOrder[i])
            {
                return i;
            }
        }

        return -1;
    }

    template<int VertexCount, int EdgeCount>
    int m(const Graph<VertexCount, EdgeCount>& f_g)
    {
        std::array<int, VertexCount> processOrder{};
        for (auto i = 0; i < VertexCount; ++i)
        {
            processOrder[i] = i;
        }

        return m(f_g, processOrder);
    }

    template<int VertexCount, int EdgeCount>
    int m(const Graph<VertexCount, EdgeCount>& f_g, const std::array<int, VertexCount>& f_processOrder)
    {
        int m{ 0 };
        for (auto it = f_g.begin(f_processOrder); it != f_g.end(); ++it)
        {
            for (const auto& [_, u, v] : it->m_outEdges)
            {
                m += p(u, f_processOrder) < p(v, f_processOrder) ? 1 : 0;
            }
        }

        return m;
    }
}
