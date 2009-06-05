package com.change_vision.jude.api.test.model;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.InputStream;

import junit.framework.Test;
import JP.co.esm.caddies.jomt.jutil.JomtUtilities2;

import com.change_vision.jude.api.inf.editor.BasicModelEditor;
import com.change_vision.jude.api.inf.editor.ModelEditorFactory;
import com.change_vision.jude.api.inf.editor.TransactionManager;
import com.change_vision.jude.api.inf.exception.InvalidEditingException;
import com.change_vision.jude.api.inf.model.IClass;
import com.change_vision.jude.api.inf.model.IComment;
import com.change_vision.jude.api.inf.model.IElement;
import com.change_vision.jude.api.inf.model.ITaggedValue;

public class IElementTest extends ITestCase {

    public static Test suite() {
        return suite("testModel/judeAPITest/IElementTest.jude", IElementTest.class);
    }

    public static Test suiteWithStream() {
        try {
            File file = new File(JomtUtilities2.getInstalledPath()+"testModel/judeAPITest/IElementNonZipTest.jude");
            InputStream in = new FileInputStream(file);
            return suite(in, IElementTest.class);
        } catch (FileNotFoundException e) {
            e.printStackTrace();
            return null;
        }
    }

    public static Test suiteWithZipStream() {
        try {
        	InputStream in = new FileInputStream(
                   new File(JomtUtilities2.getInstalledPath()+"testModel/judeAPITest/IElementTest.jude"));
           return suite(in, IElementTest.class);
       } catch (FileNotFoundException e) {
           e.printStackTrace();
           return null;
       }
    }

//    public void testGetOwner() {
//        IElement element = getElement(project.getOwnedElements(), "Class0");
//        assertEquals(project, element.getOwner());
//	}

    public void testGetOwner_null() {
        assertEquals(null, project.getOwner());
    }

	public void testGetStereotypes() {
        IElement element = getElement(project.getOwnedElements(), "Class0");
		String[] stereotypes = element.getStereotypes();
		assertEquals(2, stereotypes.length);
		assertEquals("stereotype", stereotypes[0]);
        assertEquals("stereotype2", stereotypes[1]);
        assertFalse(element.isReadOnly());
	}

	public void testGetComments() {
        IElement element = getElement(project.getOwnedElements(), "Class0");
        IComment[] comments = element.getComments();
        assertEquals(2, comments.length);
	}

    public void testIsReadOnlyClass() throws InvalidEditingException {
	        IElement element = getElement(project.getOwnedElements(), "ReadOnlyClass");
	    //IElement[] es = project.getOwnedElements();
        assertTrue(element.isReadOnly());
   }

    public void testGetTaggedValues() {
        IElement element = getElement(project.getOwnedElements(), "UseCase0");
        ITaggedValue[] taggedValues = element.getTaggedValues();
        assertEquals(4, taggedValues.length);
        assertFalse(element.isReadOnly());
    }

    public void testGetId() {
        IElement element = getElement(project.getOwnedElements(), "UseCase0");
        assertEquals("f19d6e-1077342f82b-f240dd135f0b4fbdf1febbfb27a0ca56", element.getId());
    }

    public void testAddStereotype() throws InvalidEditingException {
    	try {
			TransactionManager.beginTransaction();
	        IElement element = getElement(project.getOwnedElements(), "UseCase0");
	        element.addStereotype("addedStereotype");
	        boolean isStereotypeAdded =
	        	getString(element.getStereotypes(), "addedStereotype") != null;
	        element.removeStereotype("addedStereotype");
	        boolean isStereotypeRemoved =
	        	getString(element.getStereotypes(), "addedStereotype") == null;
			TransactionManager.endTransaction();
			assertTrue(isStereotypeAdded);
			assertTrue(isStereotypeRemoved);
    	} catch (InvalidEditingException e) {
    		TransactionManager.abortTransaction();
    		fail();
    	}
    }

    public void testAddMultiLineStereotype1() throws InvalidEditingException {
    	IElement element = null;
    	try {
			TransactionManager.beginTransaction();
	        element = getElement(project.getOwnedElements(), "UseCase0");
	        element.addStereotype("addedSter\r\neotype");
			fail();
    	} catch (InvalidEditingException e) {
	        boolean isStereotypeAdded =
	        	getString(element.getStereotypes(), "addedSter\r\neotype") != null;
			assertFalse(isStereotypeAdded);
    	} finally {
    		TransactionManager.abortTransaction();
    	}
    }

    public void testAddMultiLineStereotype2() throws InvalidEditingException {
    	IElement element = null;
    	try {
			TransactionManager.beginTransaction();
	        element = getElement(project.getOwnedElements(), "UseCase0");
	        element.addStereotype("addedSter\reotype");
			fail();
    	} catch (InvalidEditingException e) {
	        boolean isStereotypeAdded =
	        	getString(element.getStereotypes(), "addedSter\reotype") != null;
			assertFalse(isStereotypeAdded);
    	} finally {
    		TransactionManager.abortTransaction();
    	}
    }

    public void testAddMultiLineStereotype3() throws InvalidEditingException {
    	IElement element = null;
    	try {
			TransactionManager.beginTransaction();
	        element = getElement(project.getOwnedElements(), "UseCase0");
	        element.addStereotype("addedSter\neotype");
			fail();
    	} catch (InvalidEditingException e) {
	        boolean isStereotypeAdded =
	        	getString(element.getStereotypes(), "addedSter\neotype") != null;
			assertFalse(isStereotypeAdded);
    	} finally {
    		TransactionManager.abortTransaction();
    	}
    }

    public void testAddInvaildJavaClassStereotypeInUseCase() throws InvalidEditingException {
    	try {
			TransactionManager.beginTransaction();
	        IElement element = getElement(project.getOwnedElements(), "UseCase0");
	        element.addStereotype("Java Class");
			TransactionManager.endTransaction();
			fail();
    	} catch (InvalidEditingException e) {
    		TransactionManager.abortTransaction();
    	}
    }

    public void testAddInvaildJavaAttributeStereotypeInUseCase() throws InvalidEditingException {
    	try {
			TransactionManager.beginTransaction();
	        IElement element = getElement(project.getOwnedElements(), "UseCase0");
	        element.addStereotype("Java Attribute");
			TransactionManager.endTransaction();
			fail();
    	} catch (InvalidEditingException e) {
    		TransactionManager.abortTransaction();
    	}
    }

    public void testAddInvaildJavaMethodStereotypeInUseCase() throws InvalidEditingException {
    	try {
			TransactionManager.beginTransaction();
	        IElement element = getElement(project.getOwnedElements(), "UseCase0");
	        element.addStereotype("Java Method");
			TransactionManager.endTransaction();
			fail();
    	} catch (InvalidEditingException e) {
    		TransactionManager.abortTransaction();
    	}
    }

    public void testAddInvaildCSharpClassStereotypeInUseCase() throws InvalidEditingException {
    	try {
			TransactionManager.beginTransaction();
	        IElement element = getElement(project.getOwnedElements(), "UseCase0");
	        element.addStereotype("C# Class");
			TransactionManager.endTransaction();
			fail();
    	} catch (InvalidEditingException e) {
    		TransactionManager.abortTransaction();
    	}
    }

    public void testAddInvaildCSharpAttributeStereotypeInUseCase() throws InvalidEditingException {
    	try {
			TransactionManager.beginTransaction();
	        IElement element = getElement(project.getOwnedElements(), "UseCase0");
	        element.addStereotype("C# Attribute");
			TransactionManager.endTransaction();
			fail();
    	} catch (InvalidEditingException e) {
    		TransactionManager.abortTransaction();
    	}
    }

    public void testAddInvaildCSharpMethodStereotypeInUseCase() throws InvalidEditingException {
    	try {
			TransactionManager.beginTransaction();
	        IElement element = getElement(project.getOwnedElements(), "UseCase0");
	        element.addStereotype("C# Method");
			TransactionManager.endTransaction();
			fail();
    	} catch (InvalidEditingException e) {
    		TransactionManager.abortTransaction();
    	}
    }

    public void testJavaClassStereotypeInClass() throws InvalidEditingException, ClassNotFoundException {
    	BasicModelEditor bme = ModelEditorFactory.getBasicModelEditor();
    	try {
			TransactionManager.beginTransaction();

			bme.setLanguageJava(project, true);
	        IElement element = getElement(project.getOwnedElements(), "Class0");
	        element.addStereotype("Java Class");

			TransactionManager.endTransaction();

	        boolean isStereotypeAdded =
	        	getString(element.getStereotypes(), "Java Class") != null;
			assertTrue(isStereotypeAdded);
    	} catch (InvalidEditingException e) {
    		TransactionManager.abortTransaction();
    		fail();
    	}
    }

    public void testJavaClassStereotypeInClass2() throws InvalidEditingException, ClassNotFoundException {
    	BasicModelEditor bme = ModelEditorFactory.getBasicModelEditor();
    	try {
			TransactionManager.beginTransaction();

			bme.setLanguageJava(project, true);
	        IElement element = getElement(project.getOwnedElements(), "Class0");
	        element.addStereotype("Java Class");

			TransactionManager.endTransaction();
			fail();
    	} catch (InvalidEditingException e) {
    		TransactionManager.abortTransaction();

    	}
    }

    public void testJavaAttributeStereotypeInClass() throws InvalidEditingException, ClassNotFoundException {
    	BasicModelEditor bme = ModelEditorFactory.getBasicModelEditor();
    	try {
			TransactionManager.beginTransaction();

			bme.setLanguageJava(project, true);
	        IElement element = getElement(project.getOwnedElements(), "Class0");
	        element.addStereotype("Java Attribute");

			TransactionManager.endTransaction();
			fail();
    	} catch (InvalidEditingException e) {
    		TransactionManager.abortTransaction();
    	}
    }

    public void testJavaMethodStereotypeInClass() throws InvalidEditingException, ClassNotFoundException {
    	BasicModelEditor bme = ModelEditorFactory.getBasicModelEditor();
    	try {
			TransactionManager.beginTransaction();

			bme.setLanguageJava(project, true);
	        IElement element = getElement(project.getOwnedElements(), "Class0");
	        element.addStereotype("Java Method");

			TransactionManager.endTransaction();
			fail();
    	} catch (InvalidEditingException e) {
    		TransactionManager.abortTransaction();
    	}
    }

    public void testJavaAttributeStereotypeInAttribute() throws InvalidEditingException, ClassNotFoundException {
    	BasicModelEditor bme = ModelEditorFactory.getBasicModelEditor();
    	try {
			TransactionManager.beginTransaction();

			bme.setLanguageJava(project, true);
			IClass cls = (IClass) getElement(project.getOwnedElements(), "Class1");
	        IElement element = getElement(cls.getAttributes(), "attribute0");
	        element.addStereotype("Java Attribute");

			TransactionManager.endTransaction();

	        boolean isStereotypeAdded =
	        	getString(element.getStereotypes(), "Java Attribute") != null;
			assertTrue(isStereotypeAdded);
    	} catch (InvalidEditingException e) {
    		TransactionManager.abortTransaction();
    		fail();
    	}
    }

    public void testJavaClassStereotypeInAttribute() throws InvalidEditingException, ClassNotFoundException {
    	BasicModelEditor bme = ModelEditorFactory.getBasicModelEditor();
    	try {
			TransactionManager.beginTransaction();

			bme.setLanguageJava(project, true);
			IClass cls = (IClass) getElement(project.getOwnedElements(), "Class1");
	        IElement element = getElement(cls.getAttributes(), "attribute0");
	        element.addStereotype("Java Class");

			TransactionManager.endTransaction();
			fail();
    	} catch (InvalidEditingException e) {
    		TransactionManager.abortTransaction();
    	}
    }

    public void testJavaMethodStereotypeInAttribute() throws InvalidEditingException, ClassNotFoundException {
    	BasicModelEditor bme = ModelEditorFactory.getBasicModelEditor();
    	try {
			TransactionManager.beginTransaction();

			bme.setLanguageJava(project, true);
			IClass cls = (IClass) getElement(project.getOwnedElements(), "Class1");
	        IElement element = getElement(cls.getAttributes(), "attribute0");
	        element.addStereotype("Java Method");

			TransactionManager.endTransaction();
			fail();
    	} catch (InvalidEditingException e) {
    		TransactionManager.abortTransaction();
    	}
    }

    public void testJavaMethodStereotypeInMethod() throws InvalidEditingException, ClassNotFoundException {
    	BasicModelEditor bme = ModelEditorFactory.getBasicModelEditor();
    	try {
			TransactionManager.beginTransaction();

			bme.setLanguageJava(project, true);
			IClass cls = (IClass) getElement(project.getOwnedElements(), "Class1");
	        IElement element = getElement(cls.getOperations(), "operation0");
	        element.addStereotype("Java Method");

			TransactionManager.endTransaction();

	        boolean isStereotypeAdded =
	        	getString(element.getStereotypes(), "Java Method") != null;
			assertTrue(isStereotypeAdded);
    	} catch (InvalidEditingException e) {
    		TransactionManager.abortTransaction();
    		fail();
    	}
    }

    public void testCSharpClassStereotypeInClass() throws InvalidEditingException, ClassNotFoundException {
    	BasicModelEditor bme = ModelEditorFactory.getBasicModelEditor();
    	try {
			TransactionManager.beginTransaction();

			bme.setLanguageCSharp(project, true);
	        IElement element = getElement(project.getOwnedElements(), "Class0");
	        element.addStereotype("C# Class");

			TransactionManager.endTransaction();

	        boolean isStereotypeAdded =
	        	getString(element.getStereotypes(), "C# Class") != null;
			assertTrue(isStereotypeAdded);
    	} catch (InvalidEditingException e) {
    		TransactionManager.abortTransaction();
    		fail();
    	}
    }

    public void testCSharpAttributeStereotypeInClass() throws InvalidEditingException, ClassNotFoundException {
    	BasicModelEditor bme = ModelEditorFactory.getBasicModelEditor();
    	try {
			TransactionManager.beginTransaction();

			bme.setLanguageCSharp(project, true);
	        IElement element = getElement(project.getOwnedElements(), "Class0");
	        element.addStereotype("C# Attribute");

			TransactionManager.endTransaction();
			fail();
    	} catch (InvalidEditingException e) {
    		TransactionManager.abortTransaction();
    	}
    }

    public void testCSharpMethodStereotypeInClass() throws InvalidEditingException, ClassNotFoundException {
    	BasicModelEditor bme = ModelEditorFactory.getBasicModelEditor();
    	try {
			TransactionManager.beginTransaction();

			bme.setLanguageCSharp(project, true);
	        IElement element = getElement(project.getOwnedElements(), "Class0");
	        element.addStereotype("C# Method");

			TransactionManager.endTransaction();

			fail();
    	} catch (InvalidEditingException e) {
    		TransactionManager.abortTransaction();
    	}
    }

    public void testCSharpAttributeStereotypeInAttribute() throws InvalidEditingException, ClassNotFoundException {
    	BasicModelEditor bme = ModelEditorFactory.getBasicModelEditor();
    	try {
			TransactionManager.beginTransaction();

			bme.setLanguageCSharp(project, true);
			IClass cls = (IClass) getElement(project.getOwnedElements(), "Class1");
	        IElement element = getElement(cls.getAttributes(), "attribute0");
	        element.addStereotype("C# Attribute");

			TransactionManager.endTransaction();

	        boolean isStereotypeAdded =
	        	getString(element.getStereotypes(), "C# Attribute") != null;
			assertTrue(isStereotypeAdded);
    	} catch (InvalidEditingException e) {
    		TransactionManager.abortTransaction();
    		fail();
    	}
    }

    public void testCSharpClassStereotypeInAttribute() throws InvalidEditingException, ClassNotFoundException {
    	BasicModelEditor bme = ModelEditorFactory.getBasicModelEditor();
    	try {
			TransactionManager.beginTransaction();

			bme.setLanguageCSharp(project, true);
			IClass cls = (IClass) getElement(project.getOwnedElements(), "Class1");
	        IElement element = getElement(cls.getAttributes(), "attribute0");
	        element.addStereotype("C# Class");

			TransactionManager.endTransaction();

			fail();
    	} catch (InvalidEditingException e) {
    		TransactionManager.abortTransaction();
    	}
    }

    public void testCSharpMethodStereotypeInAttribute() throws InvalidEditingException, ClassNotFoundException {
    	BasicModelEditor bme = ModelEditorFactory.getBasicModelEditor();
    	try {
			TransactionManager.beginTransaction();

			bme.setLanguageCSharp(project, true);
			IClass cls = (IClass) getElement(project.getOwnedElements(), "Class1");
	        IElement element = getElement(cls.getAttributes(), "attribute0");
	        element.addStereotype("C# Method");

			TransactionManager.endTransaction();

			fail();
    	} catch (InvalidEditingException e) {
    		TransactionManager.abortTransaction();
    	}
    }

    public void testCSharpMethodStereotypeInOperation() throws InvalidEditingException, ClassNotFoundException {
    	BasicModelEditor bme = ModelEditorFactory.getBasicModelEditor();
    	try {
			TransactionManager.beginTransaction();

			bme.setLanguageCSharp(project, true);
			IClass cls = (IClass) getElement(project.getOwnedElements(), "Class1");
	        IElement element = getElement(cls.getOperations(), "operation0");
	        element.addStereotype("C# Method");

			TransactionManager.endTransaction();

	        boolean isStereotypeAdded =
	        	getString(element.getStereotypes(), "C# Method") != null;
			assertTrue(isStereotypeAdded);
    	} catch (InvalidEditingException e) {
    		TransactionManager.abortTransaction();
    		fail();
    	}
    }

    public void testCSharpClassStereotypeInOperation() throws InvalidEditingException, ClassNotFoundException {
    	BasicModelEditor bme = ModelEditorFactory.getBasicModelEditor();
    	try {
			TransactionManager.beginTransaction();

			bme.setLanguageCSharp(project, true);
			IClass cls = (IClass) getElement(project.getOwnedElements(), "Class1");
	        IElement element = getElement(cls.getOperations(), "operation0");
	        element.addStereotype("C# Class");

			TransactionManager.endTransaction();

			fail();
    	} catch (InvalidEditingException e) {
    		TransactionManager.abortTransaction();
    	}
    }

    public void testCSharpAttributeStereotypeInOperation() throws InvalidEditingException, ClassNotFoundException {
    	BasicModelEditor bme = ModelEditorFactory.getBasicModelEditor();
    	try {
			TransactionManager.beginTransaction();

			bme.setLanguageCSharp(project, true);
			IClass cls = (IClass) getElement(project.getOwnedElements(), "Class1");
	        IElement element = getElement(cls.getOperations(), "operation0");
	        element.addStereotype("C# Attribute");

			TransactionManager.endTransaction();
			fail();
    	} catch (InvalidEditingException e) {
    		TransactionManager.abortTransaction();
    	}
    }
    //----------------------------------------------------------------------
    //stereotype order test
    //----------------------------------------------------------------------
    public void testStereotypeOrder() throws InvalidEditingException, ClassNotFoundException {
    	BasicModelEditor bme = ModelEditorFactory.getBasicModelEditor();
    	try {
			TransactionManager.beginTransaction();

			bme.setLanguageJava(project, true);
			IClass cls = (IClass) getElement(project.getOwnedElements(), "Class3");
			cls.addStereotype("Java Class");
			cls.addStereotype("interface");
			cls.addStereotype("stereotype");

			TransactionManager.endTransaction();

			String[] stereotypes = cls.getStereotypes();
			assertEquals("interface", stereotypes[0]);
			assertEquals("stereotype", stereotypes[1]);
			assertEquals("Java Class", stereotypes[2]);
    	} catch (InvalidEditingException e) {
    		TransactionManager.abortTransaction();
    		fail();
    	}
    }

    public void testStereotypeOrder2() throws InvalidEditingException, ClassNotFoundException {
    	BasicModelEditor bme = ModelEditorFactory.getBasicModelEditor();
    	try {
			TransactionManager.beginTransaction();

			bme.setLanguageJava(project, true);
			IClass cls = (IClass) getElement(project.getOwnedElements(), "Class3");
			cls.removeStereotype("stereotype");

			TransactionManager.endTransaction();

			String[] stereotypes = cls.getStereotypes();
			assertEquals("interface", stereotypes[0]);
			assertEquals("Java Class", stereotypes[1]);
    	} catch (InvalidEditingException e) {
    		TransactionManager.abortTransaction();
    		fail();
    	}
    }


    //----------------------------------------------------------------------
    //common
    //----------------------------------------------------------------------
    private String getString(String[] names, String target) {
    	for (int i = 0; i < names.length; i++) {
    		if (target.equals(names[i])) {
    			return names[i];
    		}
    	}
    	return null;
    }
}
