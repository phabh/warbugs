package com.change_vision.jude.api.test.model;

import java.awt.Color;

import junit.framework.Test;

import com.change_vision.jude.api.inf.model.IElement;
import com.change_vision.jude.api.inf.model.IMatrixDiagram;
import com.change_vision.jude.api.inf.presentation.IHeaderCell;
import com.change_vision.jude.api.inf.presentation.IValueCell;

public class ICRUDDiagramTest extends ITestCase {

    public static Test suite() {
        return suite("testModel/judeAPITest/ICRUDTest.jude", ICRUDDiagramTest.class);
    }

    public void testGetDiagram() {
    	IMatrixDiagram dgm = (IMatrixDiagram)getElement(project.getDiagrams(), "CRUD0");
        assertNotNull(dgm);
    	
    	String[] rowlabels = {"UseCase Diagram0", "UseCase0", "UseCase1", "Total"};
    	String[] columnlabels = {"ER Diagram0", "Entity0", "Entity1", "Total"};
    	IHeaderCell[] columnHeaders = dgm.getColumnHeaders();
    	IHeaderCell[] columnHeaders2 = dgm.getColumnHeaders();
    	if (columnHeaders.length != 4) {
    		fail();
    	}
    	for (int i = 0; i < columnHeaders.length; i++) {
    		if (i == 0 || i == 3) {
    			IHeaderCell h = columnHeaders[i].getParent();
        		if (h != null) {
        			fail();
        		}
    		} else {
        		if (columnHeaders[i].getParent() == null) {
        			fail();
        		}
    		}
    		if (!columnlabels[i].equals(columnHeaders[i].getLabel())) {
    			fail();
    		}
    		if (!columnHeaders[i].isVisible()) {
    			fail();
    		}
    		if (!columnHeaders[i].isColumnHeader()) {
    			fail();
    		}
    		if (i == 3) {
        		if (!columnHeaders[i].isTotal()) {
        			fail();
        		}
        		IElement e = columnHeaders[i].getModel();
        		if (e != null) {
        			fail();
        		}
    		} else {
        		if (columnHeaders[i].isTotal()) {
        			fail();
        		}
        		IElement e = columnHeaders[i].getModel();
        		if (e == null) {
        			fail();
        		}
    		}
    	}
    	IHeaderCell[] showColumnHeaders = dgm.getShowColumnHeaders();
    	if (showColumnHeaders.length != 4) {
    		fail();
    	}
    	IHeaderCell[] rowHeaders = dgm.getRowHeaders();
    	if (rowHeaders.length != 4) {
    		fail();
    	}
    	for (int i = 0; i < rowHeaders.length; i++) {
    		if (i == 0 || i == 3) {
    			IHeaderCell h = rowHeaders[i].getParent();
        		if (h != null) {
        			fail();
        		}
    		} else {
        		if (rowHeaders[i].getParent() == null) {
        			fail();
        		}
    		}
    		if (!rowlabels[i].equals(rowHeaders[i].getLabel())) {
    			fail();
    		}
    		if (!rowHeaders[i].isVisible()) {
    			fail();
    		}
    		if (rowHeaders[i].isColumnHeader()) {
    			fail();
    		}
    		if (i == 3) {
        		if (!rowHeaders[i].isTotal()) {
        			fail();
        		}
        		IElement e = rowHeaders[i].getModel();
        		if (e != null) {
        			fail();
        		}
    		} else {
        		if (rowHeaders[i].isTotal()) {
        			fail();
        		}
        		IElement e = rowHeaders[i].getModel();
        		if (e == null) {
        			fail();
        		}
    		}
    	}
    	IHeaderCell[] showRowHeaders = dgm.getShowRowHeaders();
    	if (showRowHeaders.length != 4) {
    		fail();
    	}
    	
    	String[] values0 = {"CRUD","CU","RD","CRUD"};
    	String[] values1 = {"CR","C","R","CR"};
    	String[] values2 = {"UD","U","D","UD"};
    	String[] values3 = {"CRUD","CU","RD","CRUD"};
    	String[][] values = new String[4][4];
    	values[0] = values0;
    	values[1] = values1;
    	values[2] = values2;
    	values[3] = values3;
    	for (int i = 0; i < showRowHeaders.length; i++) {
    		for (int j = 0; j < showColumnHeaders.length; j++) {
    			IValueCell p = dgm.getShowValueCell(i, j);
    			String value = p.getValue();
    			Color c = p.getColor();
    			boolean isCreate = p.isCreate();
    			boolean isRead = p.isRead();
    			boolean isUpdate = p.isUpdate();
    			boolean isDelete = p.isDelete();
    			if (!values[i][j].equals(value)) {
    				fail();
    			}
    			System.out.println("ValueCell:[" + i + "][" + j + "]=" + value + " Color=" + c);
    		}
    	}
    	
    	IValueCell p = dgm.getShowValueCell(10, 10);
    	if ( p != null ) {
    		fail();
    	}
    	
    	boolean isShownByGroupRow = dgm.isRowShownByGroup();
    	if (!isShownByGroupRow) {
    		fail();
    	}
    	boolean isShownByGroupColumn = dgm.isColumnShownByGroup();
    	if (!isShownByGroupColumn) {
    		fail();
    	}
    	boolean isShownTotalRow = dgm.isRowShownTotal();
    	if (!isShownTotalRow) {
    		fail();
    	}
    	boolean isShownTotalColum = dgm.isColumnShownTotal();
    	if (!isShownTotalColum) {
    		fail();
    	}
    	boolean isShownByPhysical = dgm.isShownByPhysical();
    	if (isShownByPhysical) {
    		fail();
    	}
    	boolean isSetDiagramCellValueAutomatically = dgm.isSetDiagramCellValueAutomatically();
    	if (!isSetDiagramCellValueAutomatically) {
    		fail();
    	}
    }
    
    public void testGetDiagram2() {
    	IMatrixDiagram dgm = (IMatrixDiagram)getElement(project.getDiagrams(), "CRUD1");
        assertNotNull(dgm);

    	int columnCount = dgm.getColumnHeaders().length;
    	if (columnCount != 4) {
    		fail();
    	}

        int showColumnCount = dgm.getShowColumnHeaders().length;
    	if (showColumnCount != 2) {
    		fail();
    	}
    	
    	int rowCount = dgm.getRowHeaders().length;
    	if (rowCount != 4) {
    		fail();
    	}
    	
        int showRowCount = dgm.getShowRowHeaders().length;
    	if (showRowCount != 2) {
    		fail();
    	}
    	
    	String[] values0 = {"C","R",};
    	String[] values1 = {"U","D"};
    	String[][] values = new String[2][2];
    	values[0] = values0;
    	values[1] = values1;
    	for (int i = 0; i < showRowCount; i++) {
    		for (int j = 0; j < showColumnCount; j++) {
    			IValueCell p = dgm.getShowValueCell(i, j);
    			String value = p.getValue();
    			if (!values[i][j].equals(value)) {
    				fail();
    			}
    		}
    	}
    	
    	boolean isShownByGroupRow = dgm.isRowShownByGroup();
    	if (isShownByGroupRow) {
    		fail();
    	}
    	boolean isShownByGroupColumn = dgm.isColumnShownByGroup();
    	if (isShownByGroupColumn) {
    		fail();
    	}
    	boolean isShownTotalRow = dgm.isRowShownTotal();
    	if (isShownTotalRow) {
    		fail();
    	}
    	boolean isShownTotalColum = dgm.isColumnShownTotal();
    	if (isShownTotalColum) {
    		fail();
    	}
    	boolean isShownByPhysical = dgm.isShownByPhysical();
    	if (!isShownByPhysical) {
    		fail();
    	}
    	boolean isSetDiagramCellValueAutomatically = dgm.isSetDiagramCellValueAutomatically();
    	if (isSetDiagramCellValueAutomatically) {
    		fail();
    	}
    }
}
