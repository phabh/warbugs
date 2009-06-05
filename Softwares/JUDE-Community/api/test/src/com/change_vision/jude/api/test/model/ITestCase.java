/*
 * Created on 2005/11/09
 */
package com.change_vision.jude.api.test.model;

import java.io.IOException;
import java.io.InputStream;

import junit.extensions.TestSetup;
import junit.framework.Test;
import junit.framework.TestCase;
import junit.framework.TestSuite;
import JP.co.esm.caddies.jomt.jutil.JomtUtilities2;

import com.change_vision.jude.api.inf.exception.InvalidEditingException;
import com.change_vision.jude.api.inf.exception.LicenseNotFoundException;
import com.change_vision.jude.api.inf.exception.ProjectLockedException;
import com.change_vision.jude.api.inf.exception.ProjectNotFoundException;
import com.change_vision.jude.api.inf.model.IAssociation;
import com.change_vision.jude.api.inf.model.IAttribute;
import com.change_vision.jude.api.inf.model.IClass;
import com.change_vision.jude.api.inf.model.IClassifierTemplateParameter;
import com.change_vision.jude.api.inf.model.IDependency;
import com.change_vision.jude.api.inf.model.IDiagram;
import com.change_vision.jude.api.inf.model.IERModel;
import com.change_vision.jude.api.inf.model.IExtend;
import com.change_vision.jude.api.inf.model.IExtentionPoint;
import com.change_vision.jude.api.inf.model.IGeneralization;
import com.change_vision.jude.api.inf.model.IInclude;
import com.change_vision.jude.api.inf.model.IModel;
import com.change_vision.jude.api.inf.model.INamedElement;
import com.change_vision.jude.api.inf.model.IRealization;
import com.change_vision.jude.api.inf.model.ITaggedValue;
import com.change_vision.jude.api.inf.model.IUsage;
import com.change_vision.jude.api.inf.model.IUseCase;
import com.change_vision.jude.api.inf.project.ProjectAccessor;
import com.change_vision.jude.api.inf.project.ProjectAccessorFactory;

public abstract class ITestCase extends TestCase {

    protected static ProjectAccessor prjAccessor;
    protected static IModel project;

    protected static Test suite(final String filePath, Class cls) {
        TestSuite testSuite = new TestSuite(cls);
        TestSetup wrapper = new TestSetup(testSuite) {
            protected void setUp() {
                try {
                    prjAccessor = ProjectAccessorFactory.getProjectAccessor();
                    prjAccessor.open(JomtUtilities2.getInstalledPath()+filePath);
                    project = prjAccessor.getProject();
                } catch (Throwable e) {
                    e.printStackTrace();
                }
            }
            protected void tearDown() {
                prjAccessor.close();
            }
        };
        return wrapper;
    }

    protected static Test suite(final String filePath, Class cls, boolean isCreateTest) {
        TestSuite testSuite = new TestSuite(cls);
        TestSetup wrapper = new TestSetup(testSuite) {
            protected void setUp() {
                try {
                    prjAccessor = ProjectAccessorFactory.getProjectAccessor();
                    prjAccessor.create(JomtUtilities2.getInstalledPath() + filePath, true);
                    project = prjAccessor.getProject();
                } catch (Throwable e) {
                    e.printStackTrace();
                }
            }
            protected void tearDown() {
            	try {

            		prjAccessor.validateProject();
					prjAccessor.save();
				} catch (LicenseNotFoundException e) {
					e.printStackTrace();
				} catch (ProjectNotFoundException e) {
					e.printStackTrace();
				} catch (IOException e) {
					e.printStackTrace();
				} catch (ProjectLockedException e) {
					e.printStackTrace();
				} catch (InvalidEditingException e) {
					System.out.println(InvalidEditingException.HAS_INVALID_MODEL_MESSAGE);
				} catch (Throwable e) {
					e.printStackTrace();
				}
                prjAccessor.close();
            }
        };
        return wrapper;
    }

    protected static Test suite(final InputStream in, Class cls) {
        TestSuite testSuite = new TestSuite(cls);
        TestSetup wrapper = new TestSetup(testSuite) {
            protected void setUp() {
                try {
                    prjAccessor = ProjectAccessorFactory.getProjectAccessor();
                    prjAccessor.open(in);
                    project = prjAccessor.getProject();
                } catch (Throwable e) {
                    e.printStackTrace();
                }
            }
            protected void tearDown() {
                prjAccessor.close();
                try {
                    in.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        };
        return wrapper;
    }

    protected INamedElement getElement(INamedElement[] elements, String elementName) {
        for (int i = 0; i < elements.length; i++) {
            if (elements[i].getName().equals(elementName)) {
                return elements[i];
            }
        }
        return null;
    }

    protected ITaggedValue getTagElement(ITaggedValue[] elements, String elementName) {
        for (int i = 0; i < elements.length; i++) {
            if (elements[i].getKey().equals(elementName)) {
                return elements[i];
            }
        }
        return null;
    }

    protected String getStereotype(INamedElement element, String elementName) {
    	String[] sterotypes = element.getStereotypes();
        for (int i = 0; i < sterotypes.length; i++) {
            if (sterotypes[i].equals(elementName)) {
                return sterotypes[i];
            }
        }
        return null;
    }

    protected IAssociation getAssociation(IClass element, String elementName) {
    	IAttribute[] atts = element.getAttributes();
        for (int i = 0; i < atts.length; i++) {
        	IAssociation ass = atts[i].getAssociation();
            if (ass!= null && elementName.equals(ass.getName())) {
                return ass;
            }
        }
        return null;
    }

    protected IDependency getDependencies(IClass element, String elementName) {
    	IDependency[] deps = element.getSupplierDependencies();
        for (int i = 0; i < deps.length; i++) {
            if (deps[i].getName().equals(elementName)) {
                return deps[i];
            }
        }
        return null;
    }

    protected IUsage getUsage(IClass element, String elementName) {
    	IUsage[] deps = element.getSupplierUsages();
        for (int i = 0; i < deps.length; i++) {
            if (deps[i].getName().equals(elementName)) {
                return deps[i];
            }
        }
        return null;
    }

    protected IGeneralization getGeneralizations(IClass element, String elementName) {
    	IGeneralization[] gs = element.getGeneralizations();
        for (int i = 0; i < gs.length; i++) {
            if (gs[i].getName().equals(elementName)) {
                return gs[i];
            }
        }
        return null;
    }

    protected IRealization getClientRealizations(IClass element, String elementName) {
    	IRealization[] rs = element.getClientRealizations();
        for (int i = 0; i < rs.length; i++) {
            if (rs[i].getName().equals(elementName)) {
                return rs[i];
            }
        }
        return null;
    }

    protected IClassifierTemplateParameter getTemplateParameters(IClass element, IClassifierTemplateParameter tp) {
    	IClassifierTemplateParameter[] tps = element.getTemplateParameters();
        for (int i = 0; i < tps.length; i++) {
            if (tps[i].equals(tp)) {
                return tps[i];
            }
        }
        return null;
    }

    protected IExtend getExtends(IUseCase element, String elementName) {
    	IExtend[] extds = element.getExtends();
        for (int i = 0; i < extds.length; i++) {
            if (extds[i].getName().equals(elementName)) {
                return extds[i];
            }
        }
        return null;
    }

    protected IInclude getIncludes(IUseCase element, String elementName) {
    	IInclude[] incs = element.getIncludes();
        for (int i = 0; i < incs.length; i++) {
            if (incs[i].getName().equals(elementName)) {
                return incs[i];
            }
        }
        return null;
    }


    protected IExtentionPoint getExtensionPoint(IUseCase element, String elementName) {
    	IExtentionPoint[] extentionPoints = element.getExtensionPoints();
        for (int i = 0; i < extentionPoints.length; i++) {
            if (extentionPoints[i].getName().equals(elementName)) {
                return extentionPoints[i];
            }
        }
        return null;
    }

    protected IDiagram getDiagram(IDiagram[] diagrams, String diagramName) {
        for (int i = 0; i < diagrams.length; i++) {
            if (diagrams[i].getName().equals(diagramName)) {
                return diagrams[i];
            }
        }
        return null;
    }

    protected IERModel getERModel() {
		INamedElement[] elements = project.getOwnedElements();
		for (int i = 0; i < elements.length; i++) {
			if (elements[i] instanceof IERModel) {
				return (IERModel) elements[i];
			}
		}
		return null;
	}
}
