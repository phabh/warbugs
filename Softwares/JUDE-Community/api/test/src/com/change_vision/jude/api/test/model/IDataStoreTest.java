package com.change_vision.jude.api.test.model;

import junit.framework.Test;

import com.change_vision.jude.api.inf.model.IDataFlowDiagram;
import com.change_vision.jude.api.inf.model.IDataFlowNode;
import com.change_vision.jude.api.inf.model.IDataStore;
import com.change_vision.jude.api.inf.model.IDiagram;

public class IDataStoreTest extends ITestCase {

	public static Test suite() {
        return suite("testModel/judeAPITest/IDataFlowDiagramTest.jude", IDataStoreTest.class);
    }
	
	public void testDataStore() {
    	IDataFlowDiagram dgm = getDiagram();
    	IDataFlowNode[] dfns = dgm.getDataFlowNodes();
    	assertEquals(dfns.length, 7);
    	
    	IDataStore targetDataStore = null;
    	for (int i = 0; i < dfns.length; i++) {
			if (dfns[i] instanceof IDataStore
					&& dfns[i].getName().equals("DataStore0")) {
				targetDataStore = (IDataStore) dfns[i];
			}
		}	
    	assertNotNull(targetDataStore);   			
    	assertEquals(targetDataStore.getDataStoreID(), "DataStore0-id");
    	assertEquals(targetDataStore.getIncomings().length, 1);
    	assertEquals(targetDataStore.getOutgoings().length, 0);
    }
    
    private IDataFlowDiagram getDiagram() {
        IDiagram[] dgms = project.getDiagrams();
        for (int i = 0; i < dgms.length; i++) {
            IDiagram diagram = dgms[i];
            if ("Data Flow Diagram0".equals(diagram.getName())) {
                return (IDataFlowDiagram)diagram;
            }
        }
        fail("no diagram");
        return null;
    }
}
