package com.change_vision.jude.api.test.model;

import junit.framework.Test;

import com.change_vision.jude.api.inf.editor.BasicModelEditor;
import com.change_vision.jude.api.inf.editor.ModelEditorFactory;
import com.change_vision.jude.api.inf.editor.TransactionManager;
import com.change_vision.jude.api.inf.exception.InvalidEditingException;
import com.change_vision.jude.api.inf.model.IAttribute;
import com.change_vision.jude.api.inf.model.IClass;
import com.change_vision.jude.api.inf.model.IDependency;
import com.change_vision.jude.api.inf.model.IHyperlink;
import com.change_vision.jude.api.inf.model.INamedElement;
import com.change_vision.jude.api.inf.model.IPackage;
import com.change_vision.jude.api.inf.model.IUseCase;

public class INamedElementTest extends ITestCase {

    public static Test suite() {
        return suite("testModel/judeAPITest/IElementTest.jude", INamedElementTest.class);
    }

    public void testGetName() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class0");
        // getOwnedElement() ÇÕ getName()ÇégópÇµÇƒÇ¢ÇÈÇΩÇﬂÅAclsÇ™nullÇ≈Ç»ÇØÇÍÇŒOK
		assertNotNull(cls);
	}

    public void testIsPublicVisibility_true() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class0");
        assertTrue(cls.isPublicVisibility());
    }

    public void testIsPublicVisibility_false() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class1");
        assertFalse(cls.isPublicVisibility());
    }

    public void testIsProtectedVisibility_true() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class1");
        assertTrue(cls.isProtectedVisibility());
    }

    public void testIsProtectedVisibility_false() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class2");
        assertFalse(cls.isProtectedVisibility());
    }

    public void testIsPackageVisibility_true() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class2");
        assertTrue(cls.isPackageVisibility());
    }

    public void testIsPackageVisibility_false() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class3");
        assertFalse(cls.isPackageVisibility());
    }

    public void testIsPrivateVisibility_true() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class3");
        assertTrue(cls.isPrivateVisibility());
    }

    public void testIsPrivateVisibility_false() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class0");
        assertFalse(cls.isPrivateVisibility());
    }

    public void testGetDefinition() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class0");
        assertEquals("The definition of Class0", cls.getDefinition());
    }

    public void testConstraints() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class1");
        IAttribute attr = (IAttribute)getElement(cls.getAttributes(), "attribute0");
        assertEquals(2, attr.getConstraints().length);
    }

    public void testGetSupplierDependencies() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class1");
        IDependency[] dependencies = cls.getSupplierDependencies();
        assertEquals(2, dependencies.length);
        assertEquals("dep2-1", dependencies[0].getName());
        assertEquals("dep3-1", dependencies[1].getName());
	}

    public void testGetHyperlinks() {

        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class3");
        IHyperlink[] hyperlinks = cls.getHyperlinks();
        for (int i = 0; i < hyperlinks.length; i++) {
			IHyperlink hyperlink = hyperlinks[i];
			if(hyperlink.getComment().equals("This is file")) {
				assertEquals(true, hyperlink.isFile());
				assertEquals("JudeP.properties", hyperlink.getName());
				assertEquals("C:/Documents and Settings/y-zhou",hyperlink.getPath());
			} else if(hyperlink.getComment().equals("This is model Element")) {
				assertEquals(true, hyperlink.isModel());
				IPackage pkg = (IPackage)getElement(project.getOwnedElements(), "pkg");
				IUseCase uc = (IUseCase)getElement(pkg.getOwnedElements(), "UseCase0");
				assertEquals(uc.getId(), hyperlink.getName());
				assertEquals("",hyperlink.getPath());
			} else if(hyperlink.getComment().equals("This is URL")) {
				assertEquals(true, hyperlink.isURL());
				assertEquals("http://www.hotmail.com", hyperlink.getName());
				assertEquals("http://",hyperlink.getPath());
			}
		}
    }

//    public void testGetSupplierDependenciesWithObject() {
//        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class5");
//        IDependency[] dependencies = cls.getSupplierDependencies();
//        assertEquals(1, dependencies.length);
//        assertEquals("dep8-5", dependencies[0].getName());
//    }
//
//    public void testGetSupplierDependenciesWithClassifier() {
//        IClass cls = (IClass)getElement(project.getOwnedElements(), "Classifier0");
//        IDependency[] dependencies = cls.getSupplierDependencies();
//        assertEquals(1, dependencies.length);
//        assertEquals("self", dependencies[0].getName());
//    }

	public void testGetClientDependencies() {
        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class1");
        IDependency[] dependencies = cls.getClientDependencies();
        assertEquals(2, dependencies.length);
        assertEquals("dep1-2", dependencies[0].getName());
        assertEquals("dep1-3", dependencies[1].getName());
	}

	public void testSetName() throws ClassNotFoundException {

		try {
			TransactionManager.beginTransaction();
			BasicModelEditor bme = ModelEditorFactory.getBasicModelEditor();
			IClass iClass = bme.createClass(project, "classForTest");
			iClass.setName("nameChangedClass");
			iClass.setDefinition("Definition of the class");
			TransactionManager.endTransaction();
		} catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
		}

		IClass cls = (IClass)getElement(project.getOwnedElements(), "nameChangedClass");
		assertNotNull(cls);
		assertEquals(cls.getDefinition(), "Definition of the class");
	}

	public void testSetBadName() throws ClassNotFoundException {

		try {
			TransactionManager.beginTransaction();
			BasicModelEditor bme = ModelEditorFactory.getBasicModelEditor();
			IClass iClass = bme.createClass(project, "classForTest");
			iClass.setName("");
			TransactionManager.endTransaction();
		} catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			assertEquals(e.getKey(), InvalidEditingException.PARAMETER_ERROR_KEY);
		}
	}

	public void testSetLineBreakName1() throws ClassNotFoundException {
		try {
			TransactionManager.beginTransaction();
			BasicModelEditor bme = ModelEditorFactory.getBasicModelEditor();
			IClass iClass = bme.createClass(project, "classForTest");
			iClass.setName("class\r\nForTest");
			fail();
		} catch (InvalidEditingException e) {
			assertEquals(e.getKey(), InvalidEditingException.PARAMETER_ERROR_KEY);
		} finally {
			TransactionManager.abortTransaction();
		}
	}

	public void testSetLineBreakName2() throws ClassNotFoundException {
		try {
			TransactionManager.beginTransaction();
			BasicModelEditor bme = ModelEditorFactory.getBasicModelEditor();
			IClass iClass = bme.createClass(project, "classForTest");
			iClass.setName("class\rForTest");
			fail();
		} catch (InvalidEditingException e) {
			assertEquals(e.getKey(), InvalidEditingException.PARAMETER_ERROR_KEY);
		} finally {
			TransactionManager.abortTransaction();
		}
	}

	public void testSetLineBreakName3() throws ClassNotFoundException {
		try {
			TransactionManager.beginTransaction();
			BasicModelEditor bme = ModelEditorFactory.getBasicModelEditor();
			IClass iClass = bme.createClass(project, "classForTest");
			iClass.setName("class\nForTest");
			fail();
		} catch (InvalidEditingException e) {
			assertEquals(e.getKey(), InvalidEditingException.PARAMETER_ERROR_KEY);
		} finally {
			TransactionManager.abortTransaction();
		}
	}


//    public void testGetClientDependenciesWithObject() {
//        IClass cls = (IClass)getElement(project.getOwnedElements(), "Class5");
//        IDependency[] dependencies = cls.getClientDependencies();
//        assertEquals(1, dependencies.length);
//        assertEquals("dep5-6", dependencies[0].getName());
//
//    }

//    public void testGetClientDependenciesWithClassifier() {
//        IClass cls = (IClass)getElement(project.getOwnedElements(), "Classifier0");
//        IDependency[] dependencies = cls.getClientDependencies();
//        assertEquals(1, dependencies.length);
//        assertEquals("self", dependencies[0].getName());
//    }
    public void testSetVisibilityPublic() {
        try {
        	TransactionManager.beginTransaction();
            IClass cls = (IClass)getElement(project.getOwnedElements(), "Class0");
            cls.setVisibility(INamedElement.PUBLIC_VISIBILITY);
			TransactionManager.endTransaction();
            assertTrue(cls.isPublicVisibility());
		} catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			fail();
		}
    }

    public void testSetVisibilityProtected() {
        try {
        	TransactionManager.beginTransaction();
            IClass cls = (IClass)getElement(project.getOwnedElements(), "Class0");
            cls.setVisibility(INamedElement.PROTECTED_VISIBILITY);
			TransactionManager.endTransaction();
			assertTrue(cls.isProtectedVisibility());
		} catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			fail();
		}
    }

    public void testSetVisibilityPackage() {
        try {
        	TransactionManager.beginTransaction();
            IClass cls = (IClass)getElement(project.getOwnedElements(), "Class0");
            cls.setVisibility(INamedElement.PACKAGE_VISIBILITY);
			TransactionManager.endTransaction();
			assertTrue(cls.isPackageVisibility());
		} catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			fail();
		}
    }

    public void testSetVisibilityPrivate() {
        try {
        	TransactionManager.beginTransaction();
            IClass cls = (IClass)getElement(project.getOwnedElements(), "Class0");
            cls.setVisibility(INamedElement.PRIVATE_VISIBILITY);
			TransactionManager.endTransaction();
			assertTrue(cls.isPrivateVisibility());
		} catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			fail();
		}
    }

    public void testSetVisibilityNull() {
        try {
        	TransactionManager.beginTransaction();
            IClass cls = (IClass)getElement(project.getOwnedElements(), "Class0");
            cls.setVisibility(null);
			TransactionManager.endTransaction();
			fail();
        } catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			assertEquals(e.getKey(), InvalidEditingException.PARAMETER_ERROR_KEY);
		}
    }

    public void testSetVisibilityIllegal() {
        try {
        	TransactionManager.beginTransaction();
            IClass cls = (IClass)getElement(project.getOwnedElements(), "Class0");
            cls.setVisibility("visibility");
			TransactionManager.endTransaction();
			fail();
        } catch (InvalidEditingException e) {
			TransactionManager.abortTransaction();
			assertEquals(e.getKey(), InvalidEditingException.PARAMETER_ERROR_KEY);
		}
    }

}
