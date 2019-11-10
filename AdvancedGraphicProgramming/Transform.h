#pragma once
#include <DirectXCollision.h>
#include <vector>


namespace MCGD20182019
{
	typedef float scalar; // conversion from 'double' to 'float' requires a narrowing conversion	:: Fixed using float
	typedef DirectX::XMFLOAT3 vec3;
	typedef DirectX::XMFLOAT3X3 mat3;
	typedef DirectX::XMFLOAT4X4 mat4;
	
	class Transform;	//FORWARD DECLARATION

	struct Rotation
	{
		vec3 imm; scalar real; // campi: parte reale e immaginaria 

		static Rotation identity();// 1
		static Transform aroundX(scalar degrees);// 1
		static Transform aroundY(scalar degrees);// 1
		static Transform aroundZ(scalar degrees);// 1
		
		vec3 apply(vec3 p) const; // 2 -- si puo’ usare il prodotto!!!

		void combine(Rotation R); // 3 fa prima this poi R
		void invert();  // 7
		static Rotation blend(Rotation a, Rotation b, scalar t); // 7

		void fromMatrix(mat3 m);  // DIFFICILE, non fare
		mat3 toMatrix() const;  // 6 facile

		void fromAxisAngle(vec3 axis); // 5 |axis| = angle (in degrees)
		vec3 toAxisAngle() const; // 5 |axis| = angle (in degrees)

		void fromEulerAngles(vec3 angles); // 4
		vec3 toEulerAngles() const; // DIFFICILE, NON FARE  (13:: IMPLEMENTATO PER FARE I TEST)

		Rotation inverse() const;	// 7
		Rotation operator* (Rotation R); // 3 prodotto fra quaternioni, 
										  // quindi anche cumulazione di rotazioni
		vec3 operator() (const vec3 &p) const
		{
			return apply(p);
		} //2
	};

	// scalatura, rotazione, traslazione
	class Transform
	{
	public:
		scalar S;
		vec3 T;
		Rotation R;
		
		Transform();

		/* qui il costruttore che prende S, R, T */ // 8
		Transform(scalar scale, const vec3& position, const Rotation& rotation); //8

		// metodi per settare una trasfrmazione da...
		void lookAt(vec3 worldPos, vec3 worldTarget, vec3 worldUpvec); //9

		mat4 toMat() const; // 10
		void fromMat(mat4 M); // NO 


		// metodi in-place:
		void combine(const Transform &b); // 11 fare prima questa TR poi b
		void invert();  // 12
		void setIdentity(); // 8

		static Transform identity(); // 8
		static Transform translate(scalar dx, scalar dy, scalar dz); // 13
		static Transform translate(vec3 v);  // 13
		static Transform scale(scalar ss); // 13
		static Transform rotateX(scalar degrees); // 13
		static Transform rotateY(scalar degrees); // 13
		static Transform rotateZ(scalar degrees); // 13
		/* esempio di uso:
		   una matrice che scala di 10, poi trasla di 20 sulla x, poi ruota di 30° in X
		   Transform::rotateX( 30 ) * Transform::translate(20,0,0) * Transform::scale(10)
		*/


		// metodi out-of-place
		Transform inverse() const
		{
			Transform tmp = *this;
			tmp.invert();
			return tmp;
		}

		Transform operator* (const Transform &b) const
		{
			Transform tmp = b;
			tmp.combine(*this);
			return tmp;
		}
		vec3 operator() (const vec3 &p) const
		{
			return applyToPos(p);
		}

		vec3 applyToPos(vec3 p) const; // 1
		vec3 applyToVec(vec3 v) const; // 8
		vec3 applyToDir(vec3 d) const; // 8


		static Transform blend(const Transform &a, const Transform &b, scalar t);

	};

	/* scenegraph */
	struct Node
	{
		Transform T; // LOCAL transform
		int parent; // index in the vector of nodes
		std::vector< int > children; // indices
		int mesh; // instances of meshes to be rendered at this node
	};

	struct Scene
	{
		std::vector< Node > nodes;
		Transform globalTr(int nodeId) const;
		int cameraNode;
		void render();  // 12
		int newNode(); // 8 return index to created node
		void init(); // 2 deletes everything. Creates one node: the root (node 0) 
		void reattachUnder(int nodeI, int newParent); // 7 leaves global matrix unaffected!
		void transformGlobal(int nodeI, Transform T);  // 1
		void transformLocal(int nodeI, Transform T);   // 1
	};


	

}