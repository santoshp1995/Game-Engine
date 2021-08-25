#ifndef GRAPHICS_OBJECT_H
#define GRAPHICS_OBJECT_H

#include "MathEngine.h"
#include "ShaderObject.h"
#include "RenderMaterial.h"
#include "Model.h"
#include "BoundingSphere.h"

namespace Azul
{
	class GraphicsObject : public RenderMaterial
	{
	public:
		GraphicsObject(const Model* const _pModel, const ShaderObject* const _pShaderObject);

		// big four
		GraphicsObject() = delete;
		GraphicsObject(const GraphicsObject&) = delete;
		GraphicsObject& operator= (const GraphicsObject&) = delete;
		virtual ~GraphicsObject();

		void Render();
		void SetWorld(Azul::Matrix& world);

		const Model* GetModel() const;
		Matrix& GetWorld();

		Sphere* pCurrSphere;

	protected:
		const Model* pModel;
		Matrix* pWorld;
		const ShaderObject* pShaderObject;

	};
}

#endif