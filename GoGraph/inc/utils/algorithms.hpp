#pragma once

#include <limits>
#include <cmath>
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

        int iteration{ 1 };

        for (auto it = f_begin; it != f_end; ++it)
        {
            if (f_isLoggingActive)
            {
                std::cout << "[sssp_async] Currently: it = " << iteration << "\n";
            }

            bool changed{ false };
            const float du = dist[it->m_v];
            if (du == std::numeric_limits<float>::infinity())
                continue;

            for (const auto& [w, u, v] : it->m_outEdges)
            {
                const float newDist = du + w;

                if (newDist < dist[v])
                {
                    if (f_isLoggingActive)
                    {
                        std::cout << "[sssp_async] SSSP changed from " << dist[v] << " to " << newDist << "\n";
                    }
                    dist[v] = newDist;
                    changed = true;
                }
            }

            if (f_isLoggingActive)
            {
                std::cout << "[sssp_async] ------------- \n";
            }

            if (changed)
            {
                iteration++;
            }
        }

        if (f_isLoggingActive)
        {
            std::cout << "[sssp_async] Converged in " << iteration << " iterations.\n";
            std::cout << "[sssp_async] Shortest paths:\n";
            for(auto i = 0; i < VertexCount; ++i)
            {
                std::cout << "[sssp_async] " << f_source << " --" << dist[i] << "--> " << i << "\n";
            }
        }

        return dist;
    }
}
