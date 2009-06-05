package com.change_vision.jude.api.test.model;

import junit.framework.Test;

import com.change_vision.jude.api.inf.model.IDataFlow;
import com.change_vision.jude.api.inf.model.IDataFlowDiagram;
import com.change_vision.jude.api.inf.model.IDiagram;

public class IDataFlowTest extends ITestCase {

	public static Test suite() {
        return suite("testModel/judeAPITest/IDataFlowDiagramTest.jude", IDataFlowTest.class);
    }
	
	public void testDataFlowTest() {
    	IDataFlowDiagram dgm = getDiagram();
    	IDataFlow[] dfs = dgm.getDataFlows();
    	assertEquals(dfs.length, 6);
    	
    	IDataFlow targetDataFlow0 = null;
    	IDataFlow targetDataFlow1 = null;
    	IDataFlow targetDataFlow2 = null;
    	IDataFlow targetDataFlow3 = null;
    	IDataFlow targetDataFlow4 = null;
    	IDataFlow targetDataFlow5 = null;
    	for (int i = 0; i < dfs.length; i++) {
    		//On a diagram, "[" and "]" was deleted for viewElement.
    		//However, The name of a model contains "[" and "]".
			if (dfs[i].getName().equals("[Data0]")) {
				targetDataFlow0 = (IDataFlow) dfs[i];
			} else if (dfs[i].getName().equals("[Data1]")) {
				targetDataFlow1 = (IDataFlow) dfs[i];
			} else if (dfs[i].getName().equals("[Data2]")) {
				targetDataFlow2 = (IDataFlow) dfs[i];
			} else if (dfs[i].getName().equals("[Data3]")) {
				targetDataFlow3 = (IDataFlow) dfs[i];
			} else if (dfs[i].getName().equals("[Data4]")) {
				targetDataFlow4 = (IDataFlow) dfs[i];
			} else if (dfs[i].getName().equals("[Data5]")) {
				targetDataFlow5 = (IDataFlow) dfs[i];
			} 
		}	
    	assertNotNull(targetDataFlow0);  
    	assertEquals(targetDataFlow0.getTarget().getName(), "ProcessBox1");
    	assertEquals(targetDataFlow0.getSource().getName(), "ProcessBox0");
    	assertNotNull(targetDataFlow1);  
    	assertNotNull(targetDataFlow2);  
    	assertEquals(targetDataFlow2.getTarget().getName(), "ProcessBox0");
    	assertEquals(targetDataFlow2.getSource().getName(), "ProcessBox3");
    	assertNotNull(targetDataFlow3);  
    	assertNotNull(targetDataFlow4);  
    	assertNotNull(targetDataFlow5);  
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
