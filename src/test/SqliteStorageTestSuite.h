#include "cxxtest/TestSuite.h"

#include "boost/filesystem.hpp"

#include "sqlite/CppSQLite3.h"
#include "data/SqliteStorage.h"

class SqliteStorageTestSuite: public CxxTest::TestSuite
{
public:
	void test_storage_adds_node_successfully()
	{
		std::string databasePath = "data/SQLiteTestSuite/test.sqlite";
		int nodeCount = -1;
		{
			SqliteStorage storage(databasePath);
			storage.init();
			storage.beginTransaction();
			storage.addNode(0, "a", false);
			storage.commitTransaction();
			nodeCount = storage.getNodeCount();
		}
		boost::filesystem::remove(databasePath);

		TS_ASSERT_EQUALS(1, nodeCount);
	}

	void test_storage_removes_node_successfully()
	{
		std::string databasePath = "data/SQLiteTestSuite/test.sqlite";
		int nodeCount = -1;
		{
			SqliteStorage storage(databasePath);
			storage.init();
			storage.beginTransaction();
			int nodeId = storage.addNode(0, "a", false);
			storage.removeElement(nodeId);
			storage.commitTransaction();
			nodeCount = storage.getNodeCount();
		}
		boost::filesystem::remove(databasePath);

		TS_ASSERT_EQUALS(0, nodeCount);
	}

	void test_storage_adds_edge_successfully()
	{
		std::string databasePath = "data/SQLiteTestSuite/test.sqlite";
		int edgeCount = -1;
		{
			SqliteStorage storage(databasePath);
			storage.init();
			storage.beginTransaction();
			int sourceNodeId = storage.addNode(0, "a", false);
			int targetNodeId = storage.addNode(0, "b", false);
			storage.addEdge(0, sourceNodeId, targetNodeId);
			storage.commitTransaction();
			edgeCount = storage.getEdgeCount();
		}
		boost::filesystem::remove(databasePath);

		TS_ASSERT_EQUALS(1, edgeCount);
	}

	void test_storage_removes_edge_successfully()
	{
		std::string databasePath = "data/SQLiteTestSuite/test.sqlite";
		int edgeCount = -1;
		{
			SqliteStorage storage(databasePath);
			storage.init();
			storage.beginTransaction();
			int sourceNodeId = storage.addNode(0, "a", false);
			int targetNodeId = storage.addNode(0, "b", false);
			int edgeId = storage.addEdge(0, sourceNodeId, targetNodeId);
			storage.removeElement(edgeId);
			storage.commitTransaction();
			edgeCount = storage.getEdgeCount();
		}
		boost::filesystem::remove(databasePath);

		TS_ASSERT_EQUALS(0, edgeCount);
	}
};
